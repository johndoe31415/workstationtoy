#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "SPISlave.h"
#include "LEDOutput.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Multiplexer.h"

#define SPI_MAX_RESPONSE_LENGTH			8
#define SPI_MAX_COMMAND_LENGTH			8

#define SPI_RESPONSE_NOMOREDATA			0xff
#define SPI_RESPONSE_RESET				0xff
#define SPI_RESPONSE_INITIALVALUE		0xff

static uint8_t spiResponse[SPI_MAX_RESPONSE_LENGTH];
static uint8_t spiResponseIndex;
static uint8_t spiCommand[SPI_MAX_COMMAND_LENGTH];
static uint8_t spiCommandIndex;

void spiReset(void) {
	spiResponseIndex = SPI_MAX_RESPONSE_LENGTH;
	spiCommandIndex = 0;
	SPDR = SPI_RESPONSE_RESET;
}

static void setSpiResponse(const uint8_t *aResponse, uint8_t aResponseLength) {
	spiResponseIndex = SPI_MAX_RESPONSE_LENGTH - aResponseLength;
	memcpy(spiResponse + spiResponseIndex, aResponse, aResponseLength);
}

static void setSpiResponseByte(uint8_t aResponseByte) {
	setSpiResponse(&aResponseByte, 1);
}

static void setSpiResponseWord(uint16_t aResponseWord) {
	setSpiResponse((uint8_t*)&aResponseWord, 2);
}

static uint8_t getNextResponseByte(void) {
	static bool resetNextByte = false;
	uint8_t response;
	/* Do we need to reset? */
	if (resetNextByte) {
		spiReset();
		resetNextByte = false;
	}
	
	/* Do we have a answer? */
	if (spiResponseIndex >= SPI_MAX_RESPONSE_LENGTH) {
		/* No */
		response = SPI_RESPONSE_NOMOREDATA;
	} else {
		/* Yes, we do. */
		response = spiResponse[spiResponseIndex];
		spiResponseIndex++;
		if (spiResponseIndex == SPI_MAX_RESPONSE_LENGTH) {
			/* End of transmission, reset SPI on next ISR */
			resetNextByte = true;
		}
	}
	return response;
}

static void spiCheckRxBuffer(void) {
	if (spiCommandIndex == 0) {
		return;
	}

	switch ((enum commandByte)spiCommand[0]) {
		case CMD_GET_LED_PATTERN:
			if (spiCommandIndex != 2) return;
			if (spiCommand[1] < LED_PAR_MIN) return;
			if (spiCommand[1] > LED_PAR_MAX) return;
			setSpiResponseWord(getLEDPattern(spiCommand[1]));
			break;
		
		case CMD_SET_LED_PATTERN:
			if (spiCommandIndex != 4) return;
			if (spiCommand[1] < LED_PAR_MIN) return;
			if (spiCommand[1] > LED_PAR_MAX) return;
			setLEDPattern(spiCommand[1], (spiCommand[2] << 0) | (spiCommand[3] << 8));
			spiReset();
			break;
		
		case CMD_SET_ALL_LED:
			if (spiCommandIndex != 3) return;
			setAllLEDPattern((spiCommand[1] << 0) | (spiCommand[2] << 8));
			spiReset();
			break;
		
		case CMD_GET_TIMING:
			if (spiCommandIndex != 1) return;
			setSpiResponseByte(getTimerMaxValue());
			break;
		
		case CMD_SET_TIMING:
			if (spiCommandIndex != 2) return;
			setTimerMaxValue(spiCommand[1]);
			spiReset();
			break;
		
		case CMD_READ_KEYBOARD:
			if (spiCommandIndex != 1) return;
			setSpiResponseByte(getKeyboardRegister());
			break;
		
		case CMD_MUX_TEST:
			if (spiCommandIndex != 1 + MULTIPLEXER_CNT) return;
			uint8_t outData[MULTIPLEXER_CNT];
			muxTest(spiCommand + 1, outData);
			setSpiResponse(outData, MULTIPLEXER_CNT);
			break;
		
		case CMD_MUX_WRITE:
			if (spiCommandIndex != 1 + MULTIPLEXER_CNT) return;
			muxWriteRaw(spiCommand + 1);
			spiReset();
			break;

		default:
			return;
	}
}

static bool spiRxByte(uint8_t aByte) {
	if (spiCommandIndex >= SPI_MAX_COMMAND_LENGTH) {
		/* Buffer full. Something wrong. */
		return false;
	}
	spiCommand[spiCommandIndex] = aByte;
	spiCommandIndex++;
	spiCheckRxBuffer();
	return true;
}

ISR(SPI_STC_vect) {
	unsigned char rxData = SPDR;
	spiRxByte(rxData);
	SPDR = getNextResponseByte();
}

void spiSlaveInit(void) {
	SPCR = _BV(SPIE) | _BV(SPE);
	SPDR = SPI_RESPONSE_INITIALVALUE;
	spiReset();
}
