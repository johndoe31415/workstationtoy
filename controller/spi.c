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

static struct spi_endpoint_t selectedEndpoint;
static uint8_t savedSREGRegister;

static void spiSetSpeed(enum spi_speed_t aSpeed) {
	selectedEndpoint.speed = aSpeed;
	SPCR &= ~(_BV(SPR0) | _BV(SPR1));
	SPCR |= (aSpeed & (_BV(SPR0) | _BV(SPR1)));
	SPSR &= ~(_BV(SPI2X));
	if (aSpeed & 0x80) {
		SPSR |= _BV(SPI2X);
	}
}

void spi_deselect(void) {
	Frontpanel_SS_SetInactive();
	Frontpanel_RESET_SetInactive();
	SREG = savedSREGRegister;
}

struct spi_endpoint_t spi_get_current_endpoint(void) {
	return selectedEndpoint;
}

void spiSelectSlave(enum spi_mode_t aMode, enum spi_speed_t aSpeed) {
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

static uint8_t spi_tx_byte(uint8_t aByte) {
	SPDR = aByte;
	while (!(SPSR & _BV(SPIF)));
	return SPDR;
}

void spi_tx(void *aData, uint8_t aLength) {
	uint8_t *data = (uint8_t*)aData;
	for (uint8_t i = 0; i < aLength; i++) {
		data[i] = spi_tx_byte(data[i]);
	}
}

void spi_tx_pause(void *aData, uint8_t aLength, uint8_t aPauseAfterByteCount, uint16_t aDelayMicros) {
	uint8_t *data = (uint8_t*)aData;
	for (uint8_t i = 0; i < aLength; i++) {
		if (i == aPauseAfterByteCount) {
			delayMicroseconds(aDelayMicros);
		}
		uint8_t rxByte = spi_tx_byte(data[i]);
		if (i >= aPauseAfterByteCount) {
			data[i] = rxByte;
		}
		delayMicroseconds(15);
	}
}

static uint16_t crc_calc_byte(uint16_t aCRC, uint8_t aDataByte) {
	return _crc_ccitt_update(aCRC, aDataByte);
}

static uint16_t crc_calc_data(uint16_t aInitialCRC, const void *aData, uint8_t aLength) {
	uint16_t crc = aInitialCRC;
	for (uint8_t i = 0; i < aLength; i++) {
		crc = crc_calc_byte(crc, ((uint8_t*)aData)[i]);
	}
	return crc;
}

uint16_t crc_test(const uint8_t *a, uint8_t b) {
	return crc_calc_data(CRC_INITIAL_VALUE, a, b);
}

void spi_tx_fill_crc(void *aData, uint8_t aMasterLength) {
	uint16_t crcValue = crc_calc_byte(CRC_INITIAL_VALUE, ((uint8_t*)aData)[0]);
	crcValue = crc_calc_data(crcValue, (uint8_t*)aData + 3, aMasterLength - 3);
	*((uint16_t*)(aData + 1)) = crcValue;
}

static bool spi_tx_to_slave_raw(void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	spi_tx_fill_crc(aData, aMasterLength);

	spi_tx_pause(aData, aLength, aMasterLength, aDelayMicros);
	spi_deselect();

	uint16_t rxCRC = crc_calc_data(CRC_INITIAL_VALUE, aData + aMasterLength, aLength - aMasterLength - 2);
	bool receivedOK = *((uint16_t*)(aData + aLength - 2)) == rxCRC;

	return receivedOK;
}

bool spi_tx_to_slave(void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros) {
	for (uint8_t tryNo = 0; tryNo < 3; tryNo++) {
		bool success = spi_tx_to_slave_raw(aData, aLength, aMasterLength, aDelayMicros);
		if (success) {
			return true;
		}
		delay_millis(1);
	}
	return false;
}

void init_spi(void) {
	SPCR = _BV(SPE) | _BV(MSTR);
}


