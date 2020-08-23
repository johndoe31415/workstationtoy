#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <util/crc16.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "spi.h"
#include "hal.h"
#include "delay.h"

#define DEBUG_SPI_TRANSMITS
#define SPI_SLAVE_DEFAULT_SEQUENCE_NUMBER						0xa5
#define CRC_INITIAL_VALUE                                       0xa55a

static struct SPIEndpoint selectedEndpoint;
static uint8_t savedSREGRegister;

static const char NAME_SLAVE_FRONTPANEL[] PROGMEM = "Frontpanel";
static const char NAME_SLAVE_VOLTAGEMON[] PROGMEM = "Voltage monitor";
static const char NAME_SLAVE_CURRENTMON[] PROGMEM = "Current monitor";
static const char NAME_SLAVE_NONE[] PROGMEM = "N/A";
static const char* const descriptiveSlaveNames[] PROGMEM = {
	[SLAVE_FRONTPANEL] = NAME_SLAVE_FRONTPANEL,
	[SLAVE_VOLTAGEMON] = NAME_SLAVE_VOLTAGEMON,
	[SLAVE_CURRENTMON] = NAME_SLAVE_CURRENTMON,
	[SLAVE_NONE] = NAME_SLAVE_NONE,
};

static void spiSetSpeed(enum SPISpeed aSpeed) {
	selectedEndpoint.speed = aSpeed;
	SPCR &= ~(_BV(SPR0) | _BV(SPR1));
	SPCR |= (aSpeed & (_BV(SPR0) | _BV(SPR1)));
	SPSR &= ~(_BV(SPI2X));
	if (aSpeed & 0x80) {
		SPSR |= _BV(SPI2X);
	}
}

void spiDeselect(void) {
	Frontpanel_SS_SetInactive();
	Frontpanel_RESET_SetInactive();
	VoltageMonitor_SS_SetInactive();
	VoltageMonitor_RESET_SetInactive();
	CurrentMonitor_SS_SetInactive();
	CurrentMonitor_RESET_SetInactive();
	selectedEndpoint.slave = SLAVE_NONE;
	SREG = savedSREGRegister;
}

struct SPIEndpoint spiGetCurrentEndpoint(void) {
	return selectedEndpoint;
}

void spiSelectSlave(enum SPISlave aSlave, enum SPIAccessMode aMode, enum SPISpeed aSpeed) {
	savedSREGRegister = SREG;
	cli();

	switch (aSlave) {
		case SLAVE_FRONTPANEL:
			if (aMode == SPIACCESS_PGM) {
				Frontpanel_RESET_SetActive();
			} else {
				Frontpanel_SS_SetActive();
			}
			break;

		case SLAVE_CURRENTMON:
			if (aMode == SPIACCESS_PGM) {
				CurrentMonitor_RESET_SetActive();
			} else {
				CurrentMonitor_SS_SetActive();
			}
			break;

		case SLAVE_VOLTAGEMON:
			if (aMode == SPIACCESS_PGM) {
				VoltageMonitor_RESET_SetActive();
			} else {
				VoltageMonitor_SS_SetActive();
			}
			break;

		case SLAVE_NONE:
			spiDeselect();
			break;
	}

	spiSetSpeed(aSpeed);
	selectedEndpoint.slave = aSlave;
	selectedEndpoint.mode = aMode;
}

void selectDefaultSPISlave(enum SPISlave aSlave) {
	return spiSelectSlave(aSlave, SPIACCESS_OPERATION, SPISPEED_DIV_8);
}

static uint8_t spiTransmitByte(uint8_t aByte) {
	SPDR = aByte;
	while (!(SPSR & _BV(SPIF)));
	return SPDR;
}

void spiTransmit(void *aData, uint8_t aLength) {
	uint8_t *data = (uint8_t*)aData;
	for (uint8_t i = 0; i < aLength; i++) {
		data[i] = spiTransmitByte(data[i]);
	}
}

void spiTransmitWithPause(void *aData, uint8_t aLength, uint8_t aPauseAfterByteCount, uint16_t aDelayMicros) {
	uint8_t *data = (uint8_t*)aData;
	for (uint8_t i = 0; i < aLength; i++) {
		if (i == aPauseAfterByteCount) {
			delayMicroseconds(aDelayMicros);
		}
		uint8_t rxByte = spiTransmitByte(data[i]);
		if (i >= aPauseAfterByteCount) {
			data[i] = rxByte;
		}
		delayMicroseconds(15);
	}
}

static uint16_t crcByte(uint16_t aCRC, uint8_t aDataByte) {
	return _crc_ccitt_update(aCRC, aDataByte);
}

static uint16_t crcData(uint16_t aInitialCRC, const void *aData, uint8_t aLength) {
	uint16_t crc = aInitialCRC;
	for (uint8_t i = 0; i < aLength; i++) {
		crc = crcByte(crc, ((uint8_t*)aData)[i]);
	}
	return crc;
}

uint16_t crctest(const uint8_t *a, uint8_t b) {
	return crcData(CRC_INITIAL_VALUE, a, b);
}

void spiTransmissionGenerateCRC(void *aData, uint8_t aMasterLength) {
	uint16_t crcValue = crcByte(CRC_INITIAL_VALUE, ((uint8_t*)aData)[0]);
	crcValue = crcData(crcValue, (uint8_t*)aData + 3, aMasterLength - 3);
	*((uint16_t*)(aData + 1)) = crcValue;
}

static bool spiTransmitToSlaveRaw(enum SPISlave aSlave, void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	spiTransmissionGenerateCRC(aData, aMasterLength);

	selectDefaultSPISlave(aSlave);
	spiTransmitWithPause(aData, aLength, aMasterLength, aDelayMicros);
	spiDeselect();

	uint16_t rxCRC = crcData(CRC_INITIAL_VALUE, aData + aMasterLength, aLength - aMasterLength - 2);
	bool receivedOK = *((uint16_t*)(aData + aLength - 2)) == rxCRC;

	return receivedOK;
}

bool spiTransmitToSlave(enum SPISlave aSlave, void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	for (uint8_t tryNo = 0; tryNo < 3; tryNo++) {
		bool success = spiTransmitToSlaveRaw(aSlave, aData, aLength, aMasterLength, aDelayMicros);
		if (success) {
			return true;
		}
		delayMillis(1);
	}
	return false;
}

const char* spiGetSlaveName(enum SPISlave aSlave) {
	const char *result;
	if (aSlave <= SLAVE_NONE) {
		memcpy_P(&result, descriptiveSlaveNames + aSlave, sizeof(const char*));
	} else {
		result = NULL;
	}
	return result;
}

const char* spiGetSelectedSlaveName(void) {
	return spiGetSlaveName(selectedEndpoint.slave);
}

void initSPI(void) {
	SPCR = _BV(SPE) | _BV(MSTR);
}


