#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "SPISlave.h"

#define MAX_MESSAGE_LENGTH					21
#define MAX_VALID_COMMAND_ID				0

#define SPI_RESPONSE_RESET					0xfc
#define SPI_RESPONSE_MASTERTX				0xfd
#define SPI_RESPONSE_ERROR					0xfe

enum spiState {
	SPISTATE_MASTERTX = 0,
	SPISTATE_SLAVETX = 1,
	SPISTATE_ERROR = 2
};

typedef void (*genericFunctionPointer)(void *);

struct commandJumpTableEntry {
	uint8_t masterDataLength;
	uint8_t messageLength;
	genericFunctionPointer handler;
} PACKED;

static uint8_t sequenceNumber = 0xa5;
static enum spiState spiState;
static uint8_t spiDataBuffer[MAX_MESSAGE_LENGTH];
static uint8_t spiBufferIndex;
static struct commandJumpTableEntry activeTableEntry;
static struct commandJumpTableEntry const handlerTable[] PROGMEM = {
	{	// Command TestSPI (ID 0x0)
		.masterDataLength = 11,
		.messageLength = 21,
		.handler = (genericFunctionPointer)executeTestSPI
	},
};

static void spiCheckRxBuffer(void) {
	if (spiBufferIndex == 1) {
		uint8_t commandId = spiDataBuffer[0];
		if (commandId <= MAX_VALID_COMMAND_ID) {
			memcpy_P(&activeTableEntry, handlerTable + commandId, sizeof(struct commandJumpTableEntry));
		} else {	
			spiState = SPISTATE_ERROR;
			return;
		}
	}

	if (spiBufferIndex == activeTableEntry.masterDataLength) {
		/* Master has transmitted all data, callback! */
		if (activeTableEntry.handler) {
			sequenceNumber++;
			activeTableEntry.handler(spiDataBuffer);
		}

		/* Then hand off to slave transmit */
		spiState = SPISTATE_SLAVETX;
	}
}

static void spiReset(void) {
	spiBufferIndex = 0;
	SPDR = sequenceNumber;
	spiState = SPISTATE_MASTERTX;
}

static uint8_t spiRxTxByte(uint8_t aRXByte) {
	if ((spiBufferIndex >= MAX_MESSAGE_LENGTH) || (spiState == SPISTATE_ERROR)) {
		/* Buffer full or some other error, bail out. */
		spiState = SPISTATE_ERROR;
		return SPI_RESPONSE_ERROR;
	}

	if (spiState == SPISTATE_MASTERTX) {
		/* Fill the receive buffer */
		spiDataBuffer[spiBufferIndex] = aRXByte;
	}
	spiBufferIndex++;

	/* Then check if the message is received and prepare the answer if we have
	 * RX/TX handoff by executing the appropriate callback function */
	spiCheckRxBuffer();

	uint8_t txByte;
	/* Load the next byte for transmission */
	if (spiState == SPISTATE_SLAVETX) {
		txByte = spiDataBuffer[spiBufferIndex];
	} else {
		txByte = SPI_RESPONSE_MASTERTX;
	}

	/* If the message is complete, then perform a reset */
	if (spiBufferIndex == activeTableEntry.messageLength) {
		spiReset();
		txByte = sequenceNumber;
	}

	return txByte;
}

ISR(SPI_STC_vect) {
	uint8_t rxData = SPDR;
	uint8_t txData = spiRxTxByte(rxData);
	SPDR = txData;
}

void spiSlaveInit(void) {
	SPCR = _BV(SPIE) | _BV(SPE);
	spiReset();
}

void checkSPIForReset(void) {
	if ((PINB & _BV(PB2)) != 0) {
		spiReset();
	}
}

#ifdef POOR_MANS_ASSERTIONS
/* Poor man's assertions if there's no _Static_assert available */
void spiFieldLengthAssertions(void) {
	uint8_t TestSPIAssertion[sizeof(struct cmCmd_TestSPI) == 21 ? 0 : -1];

	(void)TestSPIAssertion;
}
#endif
