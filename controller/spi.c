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

static void spi_set_speed(enum spi_speed_t speed) {
	SPCR &= ~(_BV(SPR0) | _BV(SPR1));
	SPCR |= (speed & (_BV(SPR0) | _BV(SPR1)));
	SPSR &= ~(_BV(SPI2X));
	if (speed & 0x80) {
		SPSR |= _BV(SPI2X);
	}
}

static uint8_t spi_tx_byte(uint8_t byte) {
	SPDR = byte;
	while (!(SPSR & _BV(SPIF)));
	return SPDR;
}

static void spi_tx(void *vdata, uint8_t length) {
	uint8_t *data = (uint8_t*)vdata;
	for (uint8_t i = 0; i < length; i++) {
		data[i] = spi_tx_byte(data[i]);
	}
}

static uint16_t crc_calc_byte(uint16_t crc_value, uint8_t data_byte) {
	return _crc_ccitt_update(crc_value, data_byte);
}

static uint16_t crc_calc_data(uint16_t crc_init_value, const void *data, uint8_t length) {
	uint16_t crc = crc_init_value;
	for (uint8_t i = 0; i < length; i++) {
		crc = crc_calc_byte(crc, ((uint8_t*)data)[i]);
	}
	return crc;
}

uint16_t crc_test(const uint8_t *a, uint8_t b) {
	return crc_calc_data(CRC_INITIAL_VALUE, a, b);
}

void spi_tx_fill_crc(void *data, uint8_t master_length) {
	uint16_t crcValue = crc_calc_byte(CRC_INITIAL_VALUE, ((uint8_t*)data)[0]);
	crcValue = crc_calc_data(crcValue, (uint8_t*)data + 3, master_length - 3);
	*((uint16_t*)(data + 1)) = crcValue;
}

void spi_tx_pause(void *vdata, uint8_t length, uint8_t pause_after_byte_count, uint16_t delay_microseconds) {
	uint8_t *data = (uint8_t*)vdata;
	for (uint8_t i = 0; i < length; i++) {
		if (i == pause_after_byte_count) {
			delayMicroseconds(delay_microseconds);
		}
		uint8_t rxByte = spi_tx_byte(data[i]);
		if (i >= pause_after_byte_count) {
			data[i] = rxByte;
		}
		delayMicroseconds(15);
	}
}

static bool spi_tx_to_slave_raw(void *data, uint8_t length, uint8_t master_length, uint16_t delay_microseconds) {
	spi_tx_fill_crc(data, master_length);

	Frontpanel_SS_SetActive();
	spi_tx_pause(data, length, master_length, delay_microseconds);
	Frontpanel_SS_SetInactive();

	uint16_t rx_crc = crc_calc_data(CRC_INITIAL_VALUE, data + master_length, length - master_length - 2);
	bool received_ok = *((uint16_t*)(data + length - 2)) == rx_crc;

	return received_ok;
}

bool spi_tx_to_slave(void *data, uint8_t length, uint8_t master_length, uint16_t delay_microseconds) {
	for (uint8_t try_no = 0; try_no < 3; try_no++) {
		bool success = spi_tx_to_slave_raw(data, length, master_length, delay_microseconds);
		if (success) {
			return true;
		}
		delay_millis(1);
	}
	return false;
}

void init_spi(void) {
	SPCR = _BV(SPE) | _BV(MSTR);
	spi_set_speed(SPISPEED_DIV_32);
	Frontpanel_RESET_SetInactive();
	Frontpanel_SS_SetInactive();
}
