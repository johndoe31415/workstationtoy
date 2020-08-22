#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Delay.h"
#include "SPI.h"
#include "Debug.h"
#include "md5.h"
#include "PayloadFrontpanel.h"
#include "PayloadCurrentMonitor.h"
#include "PayloadVoltageMonitor.h"
#include "Mega8Programmer.h"
#include "Panic.h"

static enum detectedChip detectedChip;

static bool enableProgramming(void) {
	uint8_t data[4];
	memset(data, 0, sizeof(data));
	data[0] = 0xac;
	data[1] = 0x53;
	spiTransmit(data, sizeof(data));
	return data[2] == 0x53;
}

static bool performChipReset(void) {
	struct SPIEndpoint currentEP = spiGetCurrentEndpoint();
	spiDeselect();
	delayMillis(30);
	spiSelectSlave(currentEP.slave, currentEP.mode, currentEP.speed);
	return enableProgramming();
}


static uint8_t readSignatureByte(uint8_t aByteNo) {
	softassert(aByteNo <= 3);
	uint8_t data[4];
	memset(data, 0, sizeof(data));
	data[0] = 0x30;
	data[2] = aByteNo;
	spiTransmit(data, sizeof(data));
	return data[3];
}

static uint32_t readDeviceIdentification(void) {
	uint32_t result = 0;
	for (uint8_t i = 0; i < 3; i++) {
		result <<= 8;
		result |= readSignatureByte(i);
	}
	return result;
}

static uint8_t readFlashByte(uint32_t aAddress) {
	uint8_t data[4];
	data[0] = 0x20 | ((aAddress & 0x01) << 3);
	data[1] = (aAddress & 0x1e00) >> 9;
	data[2] = (aAddress & 0x01fe) >> 1;
	data[3] = 0;
	spiTransmit(data, sizeof(data));
	return data[3];
}

static void performChipErase(void) {
	uint8_t data[4];
	memset(data, 0, sizeof(data));
	data[0] = 0xac;
	data[1] = 0x80;
	spiTransmit(data, sizeof(data));
	delayMillis(10);
}


/* aAddress refers to byte within that page, i.e from 0 to (ATMEGA8_PAGESIZE - 1) */
static void loadProgramMemoryByte(uint16_t aAddress, uint8_t aData) {
	softassert(detectedChip != CHIP_NONE);
	softassert(((detectedChip == CHIP_ATMEGA8) && (aAddress < ATMEGA8_PAGESIZE)) || ((detectedChip == CHIP_ATMEGA88) && (aAddress < ATMEGA88_PAGESIZE)));
	uint8_t data[4];
	data[0] = 0x40 | ((aAddress & 0x01) << 3);
	data[1] = 0;
	data[2] = (aAddress & 0x3e) >> 1;
	data[3] = aData;
	spiTransmit(data, sizeof(data));
}

static void loadProgramMemoryPage(const uint8_t *aPageData) {
	for (uint8_t i = 0; i < ATMEGA8_PAGESIZE; i++) {
		loadProgramMemoryByte(i, aPageData[i]);
	}
}

static void writeProgramMemoryPage(uint16_t aPageNo) {
	uint8_t data[4];
	data[0] = 0x4c;
	data[1] = (aPageNo & 0x78) >> 3;
	data[2] = (aPageNo & 0x7) << 5;
	data[3] = 0;
	spiTransmit(data, sizeof(data));
	delayMillis(5);
}

static uint32_t readFuseBits(void) {
	uint32_t fuseBits = 0;
	if ((detectedChip == CHIP_ATMEGA8) || (detectedChip == CHIP_ATMEGA88)) {
		uint8_t data[4];

		/* Read fuse bits */
		memset(data, 0, sizeof(data));
		data[0] = 0x50;
		spiTransmit(data, sizeof(data));
		fuseBits |= ((uint32_t)data[3] << 0);

		/* Read fuse high bits */
		memset(data, 0, sizeof(data));
		data[0] = 0x58;
		data[1] = 0x08;
		spiTransmit(data, sizeof(data));
		fuseBits |= ((uint32_t)data[3] << 8);

		if (detectedChip == CHIP_ATMEGA88) {
			/* Read extended fuse bits (only ATmega88) */
			memset(data, 0, sizeof(data));
			data[0] = 0x50;
			data[1] = 0x08;
			spiTransmit(data, sizeof(data));
			fuseBits |= ((uint32_t)data[3] << 16);
		}
	} else {
		logmsg("%S: Unable to read fuse bits for device %u\r\n", spiGetSelectedSlaveName(), detectedChip);
	}
	return fuseBits;
}

static void writeFuseBits(uint32_t aFuseConfig) {
	if ((detectedChip == CHIP_ATMEGA8) || (detectedChip == CHIP_ATMEGA88)) {
		uint8_t data[4];

		/* Write fuse bits */
		data[0] = 0xac;
		data[1] = 0xa0;
		data[2] = 0x00;
		data[3] = (aFuseConfig & 0xffUL) >> 0;
		spiTransmit(data, sizeof(data));

		/* Write fuse high bits */
		data[0] = 0xac;
		data[1] = 0xa8;
		data[2] = 0x00;
		data[3] = (aFuseConfig & 0xff00UL) >> 8;
		spiTransmit(data, sizeof(data));

		if (detectedChip == CHIP_ATMEGA88) {
			/* Write extended fuse bits (only ATmega88) */
			data[0] = 0xac;
			data[1] = 0xa4;
			data[2] = 0x00;
			data[3] = (aFuseConfig & 0xff0000UL) >> 16;
			spiTransmit(data, sizeof(data));
		}
		performChipReset();
	} else {
		logmsg("%S: Unable to write fuse bits for device %u\r\n", spiGetSelectedSlaveName(), detectedChip);
	}
}


static bool initProgramming(enum SPISlave aSlave) {
	detectedChip = CHIP_NONE;

	spiSelectSlave(aSlave, SPIACCESS_PGM, SPISPEED_DIV_8);
	delayMillis(20);
	if (!enableProgramming()) {
		logmsg("%S: Programming enabled failed, trying again with reduced speed\r\n", spiGetSelectedSlaveName());
		spiDeselect();
		delayMillis(1);
		spiSelectSlave(aSlave, SPIACCESS_PGM, SPISPEED_DIV_128);
		delayMillis(20);
		if (!enableProgramming()) {
			logmsg("%S: Enable programming also failed with fallback SPI source\r\n", spiGetSelectedSlaveName());
			spiDeselect();
			return false;
		} else {
			logmsg("%S: Enable programming succeeded with reduced speed\r\n", spiGetSelectedSlaveName());
		}
	}

	uint32_t deviceId = readDeviceIdentification();
	if (deviceId == ATMEGA8_IDENTIFIER) {
		detectedChip = CHIP_ATMEGA8;
		logmsg("%S: Detected ATmega8\r\n", spiGetSelectedSlaveName());
	} else if (deviceId == ATMEGA88_IDENTIFIER) {
		detectedChip = CHIP_ATMEGA88;
		logmsg("%S: Detected ATmega88\r\n", spiGetSelectedSlaveName());
	} else {
		logmsg("%S: Received unknown deviceId 0x%lx\r\n", spiGetSelectedSlaveName(), deviceId);
		spiDeselect();
		return false;
	}

	return true;
}

static bool checkSpecificDeviceFuseConfig(const char *aDeviceName, uint32_t aExpectedFuseConfig) {
	uint32_t fuseConfig;
	fuseConfig = readFuseBits();
	logmsg("%S: Current slave fuse configuration is 0x%lx\r\n", spiGetSelectedSlaveName(), fuseConfig);

	if (fuseConfig != aExpectedFuseConfig) {
		logmsg("%S: Expected slave fuse configuration for %S is 0x%lx (XOR 0x%lx), reprogramming...\r\n", spiGetSelectedSlaveName(), aDeviceName, aExpectedFuseConfig, aExpectedFuseConfig ^ fuseConfig);
		writeFuseBits(aExpectedFuseConfig);

		fuseConfig = readFuseBits();
		if (fuseConfig == aExpectedFuseConfig) {
			logmsg("%S: Writing fuse bits succeeded\r\n", spiGetSelectedSlaveName());
		} else {
			logmsg("%S: Writing fuse bits failed, read back 0x%lx (XOR 0x%lx)\r\n", spiGetSelectedSlaveName(), fuseConfig, aExpectedFuseConfig ^ fuseConfig);
			return false;
		}
	} else {
		logmsg("%S: Fuse bits are OK\r\n", spiGetSelectedSlaveName());
	}
	return true;
}

static bool checkDeviceFuseConfig(void) {
	if (detectedChip == CHIP_ATMEGA8) {
		return checkSpecificDeviceFuseConfig(PSTR("ATmega8"), ATMEGA8_FUSECONFIG);
	} else if (detectedChip == CHIP_ATMEGA88) {
		return checkSpecificDeviceFuseConfig(PSTR("ATmega88"), ATMEGA88_FUSECONFIG);
	} else {
		logmsg("%S: Don't know how to check fuses of device 0x%x\r\n", spiGetSelectedSlaveName(), detectedChip);
		return false;
	}
}

static bool isPayloadIntact(const uint8_t *aPayloadData, uint16_t aPayloadLen) {
	logmsg("%S: Verifying %d bytes slave payload (stored @%p)\r\n", spiGetSelectedSlaveName(), aPayloadLen, aPayloadData);
	for (uint16_t i = 0; i < aPayloadLen; i++) {
		uint8_t flashByte = readFlashByte(i);
		uint8_t correctByte = pgm_read_byte(aPayloadData + i);
		if (flashByte != correctByte) {
			logmsg("%S: Payload differs at offset 0x%x, flash storage 0x%x correct byte 0x%x.\r\n", spiGetSelectedSlaveName(), i, flashByte, correctByte);
			return false;
		}
	}
	return true;
}

static bool verifySlaveProgramming(enum SPISlave aSlave, const uint8_t *aPayloadData, uint16_t aPayloadLen) {
	logmsg("Checking integrity of slave '%S'\r\n", spiGetSlaveName(aSlave));
	
	if (!initProgramming(aSlave)) {
		logmsg("%S: cannot initiate programming mode (slave not present?)\r\n", spiGetSelectedSlaveName());
		return false;
	}
	
	if (!checkDeviceFuseConfig()) {
		logmsg("%S: fuses have incorrect values or are not reprogrammable\r\n", spiGetSelectedSlaveName());
		spiDeselect();
		return false;
	}

	if (isPayloadIntact(aPayloadData, aPayloadLen)) {
		logmsg("%S: payload is intact\r\n", spiGetSelectedSlaveName());
		spiDeselect();
		return true;
	}

	logmsg("%S: payload is NOT intact\r\n", spiGetSelectedSlaveName());
	performChipErase();
	{
		uint16_t pageCount = (aPayloadLen + ATMEGA8_PAGESIZE - 1) / ATMEGA8_PAGESIZE;
		uint16_t lastPayloadSize;
		lastPayloadSize = ((aPayloadLen % ATMEGA8_PAGESIZE) == 0) ? ATMEGA8_PAGESIZE : (aPayloadLen % ATMEGA8_PAGESIZE);
		for (uint16_t pageNo = 0; pageNo < pageCount; pageNo++) {
			uint8_t pageData[ATMEGA8_PAGESIZE];

			/* Load page from Flash into RAM */
			uint16_t actualPageSize;
			actualPageSize = (pageNo < (pageCount - 1)) ? ATMEGA8_PAGESIZE : lastPayloadSize;
			memset(pageData, 0xff, ATMEGA8_PAGESIZE);
			memcpy_P(pageData, aPayloadData + (pageNo * ATMEGA8_PAGESIZE), actualPageSize);

			logmsg("%S: Programming page #%d of %d len %d\r\n", spiGetSelectedSlaveName(), pageNo, pageCount, actualPageSize);
			
			/* Load that page into the Program Memory Page of the slave controller */
			loadProgramMemoryPage(pageData);

			/* Initiate programming of the slave page */
			writeProgramMemoryPage(pageNo);
		}
	}

	if (isPayloadIntact(aPayloadData, aPayloadLen)) {
		logmsg("%S: verify successful, programming succeeded.\r\n", spiGetSelectedSlaveName());
		spiDeselect();
		return true;
	}
	
	logmsg("%S: Verify FAILED, programming unsuccessful.\r\n", spiGetSelectedSlaveName());
	spiDeselect();
	return false;
}

void initSlaveDevices(void) {
	if (!verifySlaveProgramming(SLAVE_FRONTPANEL, payloadFrontpanel, LEN_PAYLOAD_FRONTPANEL)) {
		panic(ERR_SLAVE_DEFECT_FRONTPANEL);
	}
	
	if (!verifySlaveProgramming(SLAVE_CURRENTMON, payloadCurrentMonitor, LEN_PAYLOAD_CURRENTMONITOR)) {
		panic(ERR_SLAVE_DEFECT_CURRENTMONITOR);
	}

	/* Wait until slaves are present */
	delayMillis(50);
}

