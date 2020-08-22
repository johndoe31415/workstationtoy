#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "LEDOutput.h"
#include "Multiplexer.h"

#define MUX(byteno, outputno)			((8 * (byteno)) + (outputno))

static uint16_t ledPattern[LEDCOUNT];
static uint8_t currentBit;
static uint8_t ledMapping[LEDCOUNT] = {
	MUX(2, 7), MUX(2, 6), MUX(2, 5), MUX(2, 4), MUX(2, 3), MUX(2, 2), MUX(2, 1),
	MUX(1, 7), MUX(1, 6), MUX(1, 5), MUX(1, 4), MUX(1, 3), MUX(1, 2), MUX(1, 1),
	MUX(0, 7), MUX(0, 6), MUX(0, 5), MUX(0, 4), MUX(0, 3), MUX(0, 2)
};

static void setLED(uint8_t aLed, bool aValue) {
	uint8_t outBit = ledMapping[aLed];
	muxSetBit(outBit, aValue);
}

void setLEDPattern(uint8_t aLed, uint16_t aPattern) {
	ledPattern[aLed] = aPattern;
}

uint16_t getLEDPattern(uint8_t aLed) {
	return ledPattern[aLed];
}

void ledTick(void) {
	currentBit += 1;
	if (currentBit >= 16) {
		currentBit = 0;
	}
	
	uint16_t bitValue = 1 << currentBit;
	for (uint8_t i = 0; i < LEDCOUNT; i++) {
		setLED(i, (ledPattern[i] & bitValue) != 0);
	}
	muxCommitOnChange();
}

void setAllLEDPattern(uint16_t aPattern) {
	for (uint8_t i = 0; i < LEDCOUNT; i++) {
		ledPattern[i] = aPattern;
	}
}

void ledInit(void) {
	muxInit();
	memset(ledPattern, 0, sizeof(ledPattern));
}

