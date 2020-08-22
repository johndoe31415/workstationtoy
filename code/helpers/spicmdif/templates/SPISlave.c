#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/crc16.h>

#include "SPISlave.h"

#define MAX_MESSAGE_LENGTH					${cmddef.getmaxmsglength()}
#define MAX_VALID_COMMAND_ID				${cmddef.getmaxcmdid()}

#define SPI_RESPONSE_RESET					0xfc
#define SPI_RESPONSE_MASTERTX				0xfd
#define SPI_RESPONSE_ERROR					0xfe
#define SPI_RESPONSE_CRCERROR				0xce

#define CRC_INITIAL_VALUE					0xa55a

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
};

struct genericMasterCommand {
	uint8_t masterCmdId;
	uint16_t crc;
	uint8_t data[];
};

static uint8_t sequenceNumber = 0xa5;
static enum spiState spiState;
static uint8_t spiDataBuffer[MAX_MESSAGE_LENGTH];
static uint8_t spiBufferIndex;
static struct commandJumpTableEntry activeTableEntry;
static struct commandJumpTableEntry const handlerTable[] PROGMEM = {
%for cmd in cmddef.cmds:
	{	// Command ${cmd.name} (ID ${hex(cmd.cmdid)})
		.masterDataLength = ${cmd.masterlen},
		.messageLength = ${len(cmd)},
		.handler = (genericFunctionPointer)execute${cmd.name}
	},
%endfor
};

static uint16_t crcByte(uint16_t aCRC, uint8_t aDataByte) {
	return _crc_ccitt_update(aCRC, aDataByte);
}

static uint16_t crcData(uint16_t aInitialCRC, const uint8_t *aData, uint8_t aLength) {
	uint16_t crc = aInitialCRC;
	for (uint8_t i = 0; i < aLength; i++) {
		crc = crcByte(crc, aData[i]);
	}
	return crc;
}

static bool masterCRCCheck(uint8_t aMasterDataLength) {
	struct genericMasterCommand *cmd = (struct genericMasterCommand*)spiDataBuffer;
	uint16_t crc = crcByte(CRC_INITIAL_VALUE, cmd->masterCmdId);
	crc = crcData(crc, cmd->data, aMasterDataLength - 3);
	return crc == cmd->crc;
}

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
		/* Master has transmitted all data, check data for integrity */
		if (masterCRCCheck(activeTableEntry.masterDataLength)) {
			if (activeTableEntry.handler) {
				sequenceNumber++;
				activeTableEntry.handler(spiDataBuffer);

				/* After the callback, do an integrity check */
				uint16_t slaveCRC = crcData(CRC_INITIAL_VALUE, spiDataBuffer + activeTableEntry.masterDataLength, activeTableEntry.messageLength - activeTableEntry.masterDataLength - 2);
				*((uint16_t*)(spiDataBuffer + activeTableEntry.messageLength - 2)) = slaveCRC;
			}

			/* Then hand off to slave transmit */
			spiState = SPISTATE_SLAVETX;
		} else {
			/* Receive CRC error, terminate */
			spiState = SPISTATE_ERROR;
		}
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
%for cmd in cmddef.cmds:
	uint8_t ${cmd.name}Assertion[sizeof(struct ${cmddef.getproperty("cmdprefix")}${cmd.name}) == ${len(cmd)} ? 0 : -1];
%endfor

%for cmd in cmddef.cmds:
	(void)${cmd.name}Assertion;
%endfor
}
#endif
