#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>

enum SPISlave {
	SLAVE_FRONTPANEL = 0,
	SLAVE_VOLTAGEMON = 1,
	SLAVE_CURRENTMON = 2,
	SLAVE_NONE = 3,
};

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
	enum SPISlave slave;
	enum SPIAccessMode mode;
	enum SPISpeed speed;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void spiDeselect(void);
struct SPIEndpoint spiGetCurrentEndpoint(void);
void spiSelectSlave(enum SPISlave aSlave, enum SPIAccessMode aMode, enum SPISpeed aSpeed);
void selectDefaultSPISlave(enum SPISlave aSlave);
void spiTransmit(void *aData, uint8_t aLength);
void spiTransmitWithPause(void *aData, uint8_t aLength, uint8_t aPauseAfterByteCount, uint16_t aDelayMicros);
void spiTransmisisonGenerateCRC(void *aData, uint8_t aMasterLength);
bool spiTransmitToSlave(enum SPISlave aSlave, void *aData, uint8_t aLength, uint8_t aMasterLength, uint16_t aDelayMicros);
const char* spiGetSlaveName(enum SPISlave aSlave);
const char* spiGetSelectedSlaveName(void);
void initSPI(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
