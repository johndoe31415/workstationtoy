#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>

enum SPIAccessMode {
	SPIACCESS_PGM,
	SPIACCESS_OPERATION,
};

enum SPISpeed {
	SPISPEED_DIV_2 = 0x80,
	SPISPEED_DIV_4 = 0,
	SPISPEED_DIV_8 = _BV(SPR0) | 0x80,
	SPISPEED_DIV_16 = _BV(SPR0),
	SPISPEED_DIV_32 = _BV(SPR1) | 0x80,
	SPISPEED_DIV_64 = _BV(SPR1),
	SPISPEED_DIV_128 = _BV(SPR0) | _BV(SPR1),
};

struct SPIEndpoint {
	enum SPIAccessMode mode;
	enum SPISpeed speed;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void spiDeselect(void);
struct SPIEndpoint spiGetCurrentEndpoint(void);
void spiSelectSlave(enum SPIAccessMode aMode, enum SPISpeed aSpeed);
void spi_tx(void *aData, uint8_t aLength);
void spi_tx_pause(void *aData, uint8_t aLength, uint8_t aPauseAfterByteCount, uint16_t aDelayMicros);
uint16_t crc_test(const uint8_t *a, uint8_t b);
void spi_tx_fill_crc(void *aData, uint8_t aMasterLength);
bool spi_tx_to_slave(void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros);
void init_spi(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
