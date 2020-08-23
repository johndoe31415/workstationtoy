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
	SREG = savedSREGRegister;
}

struct SPIEndpoint spiGetCurrentEndpoint(void) {
	return selectedEndpoint;
}

void spiSelectSlave(enum SPIAccessMode aMode, enum SPISpeed aSpeed) {
	savedSREGRegister = SREG;
	cli();

	if (aMode == SPIACCESS_PGM) {
		Frontpanel_RESET_SetActive();
	} else {
		Frontpanel_SS_SetActive();
	}

	spiSetSpeed(aSpeed);
	selectedEndpoint.mode = aMode;
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

static bool spiTransmitToSlaveRaw(void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	spiTransmissionGenerateCRC(aData, aMasterLength);

	spiTransmitWithPause(aData, aLength, aMasterLength, aDelayMicros);
	spiDeselect();

	uint16_t rxCRC = crcData(CRC_INITIAL_VALUE, aData + aMasterLength, aLength - aMasterLength - 2);
	bool receivedOK = *((uint16_t*)(aData + aLength - 2)) == rxCRC;

	return receivedOK;
}

bool spiTransmitToSlave(void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	for (uint8_t tryNo = 0; tryNo < 3; tryNo++) {
		bool success = spiTransmitToSlaveRaw(aData, aLength, aMasterLength, aDelayMicros);
		if (success) {
			return true;
		}
		delay_millis(1);
	}
	return false;
}

void initSPI(void) {
	SPCR = _BV(SPE) | _BV(MSTR);
}


