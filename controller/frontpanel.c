#include <stdint.h>
#include <string.h>

#include <avr/pgmspace.h>

#include "frontpanel.h"
#include "spi.h"
#include "delay.h"

struct led_pattern_t {
	uint16_t green;
	uint16_t red;
};

static const struct led_pattern_t patterns[] PROGMEM = {
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

static void led_state_to_pattern(enum FrontpanelLEDState aState, struct led_pattern_t *aPattern) {
	memcpy_P(aPattern, patterns + aState, sizeof(struct led_pattern_t));
}

void setLED(enum fpEnum_ledIndex aLED, enum FrontpanelLEDState aState) {
	struct led_pattern_t pattern;
	led_state_to_pattern(aState, &pattern);

	struct fpCmd_SetLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
	cmd.master.ledIndex = aLED;
	cmd.master.patternRed = pattern.red;
	cmd.master.patternGreen = pattern.green;

	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, sizeof(cmd), sizeof(cmd.master), FP_SETLEDPATTERN_DELAY_US);
}

static void led_test_specific(enum fpEnum_ledIndex aLED) {
	setLED(aLED, STATE_GREEN);
	delay_millis(500);
	setLED(aLED, STATE_RED);
	delay_millis(500);
	setLED(aLED, STATE_ORANGE);
	delay_millis(500);
	setLED(aLED, STATE_OFF);
}

void ledTest(void) {
	led_test_specific(LED_OPERATION);
	led_test_specific(LED_ERROR);
	led_test_specific(LED_AUTOMATIC_SHUTDOWN);
	led_test_specific(LED_TEMPERATURE);
	led_test_specific(LED_PROTECTIVE_EARTH);
	led_test_specific(LED_PHASE_ERROR);
	led_test_specific(LED_OVERCURRENT);
	led_test_specific(LED_AUTO_TRANSFORMER);
	led_test_specific(LED_ISOLATION_TRANSFORMER);
	led_test_specific(LED_OUTPUT);
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
