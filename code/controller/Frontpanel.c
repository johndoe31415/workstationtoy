#include <stdint.h>
#include <string.h>

#include <avr/pgmspace.h>

#include "Frontpanel.h"
#include "SPI.h"
#include "Debug.h"
#include "Delay.h"

struct ledPattern {
	uint16_t green;
	uint16_t red;
};

static const struct ledPattern patterns[] PROGMEM = {
	[STATE_OFF] = {
		.green	= 0x0000,
		.red	= 0x0000,
	},
	[STATE_GREEN] = {
		.green	= 0xffff,
		.red	= 0x0000,
	},
	[STATE_RED] = {
		.green	= 0x0000,
		.red	= 0xffff,
	},
	[STATE_ORANGE] = {
		.green	= 0xffff,
		.red	= 0xffff,
	},
	[STATE_BLINK_ORANGE_SLOW] = {
		.green	= 0xf0f0,
		.red	= 0xf0f0,
	},
	[STATE_BLINK_RED_FAST] = {
		.green	= 0x0000,
		.red	= 0xaaaa,
	},
};

static void ledStateToPattern(enum FrontpanelLEDState aState, struct ledPattern *aPattern) {
	memcpy_P(aPattern, patterns + aState, sizeof(struct ledPattern));
}

void setLED(enum fpEnum_ledIndex aLED, enum FrontpanelLEDState aState) {
	struct ledPattern pattern;
	ledStateToPattern(aState, &pattern);

	struct fpCmd_SetLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
	cmd.master.ledIndex = aLED;
	cmd.master.patternRed = pattern.red;
	cmd.master.patternGreen = pattern.green;
	
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, sizeof(cmd), sizeof(cmd.master), FP_SETLEDPATTERN_DELAY_US);
}

static void ledTestSpecific(enum fpEnum_ledIndex aLED) {
	setLED(aLED, STATE_GREEN);
	delayMillis(500);
	setLED(aLED, STATE_RED);
	delayMillis(500);
	setLED(aLED, STATE_ORANGE);
	delayMillis(500);
	setLED(aLED, STATE_OFF);
}

void ledTest(void) {
	ledTestSpecific(LED_OPERATION);
	ledTestSpecific(LED_ERROR);
	ledTestSpecific(LED_AUTOMATIC_SHUTDOWN);
	ledTestSpecific(LED_TEMPERATURE);
	ledTestSpecific(LED_PROTECTIVE_EARTH);
	ledTestSpecific(LED_PHASE_ERROR);
	ledTestSpecific(LED_OVERCURRENT);
	ledTestSpecific(LED_AUTO_TRANSFORMER);
	ledTestSpecific(LED_ISOLATION_TRANSFORMER);
	ledTestSpecific(LED_OUTPUT);
}

struct KeyboardEvent getFrontpanelKey(void) {
	struct fpCmd_ReadKeyboard cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_READKEYBOARD_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, sizeof(cmd), sizeof(cmd.master), FP_READKEYBOARD_DELAY_US);

	struct KeyboardEvent returnValue;
	returnValue.eventType = cmd.slave.keyboardEvent;
	returnValue.key = cmd.slave.pressedKey;
	return returnValue;
}

