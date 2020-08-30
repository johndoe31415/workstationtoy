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

static void led_state_to_pattern(enum led_state_t state, struct led_pattern_t *pattern) {
	memcpy_P(pattern, patterns + state, sizeof(struct led_pattern_t));
}

void fp_set_led(enum fpEnum_ledIndex led, enum led_state_t state) {
	struct led_pattern_t pattern;
	led_state_to_pattern(state, &pattern);

	struct fpCmd_SetLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
	cmd.master.ledIndex = led;
	cmd.master.patternRed = pattern.red;
	cmd.master.patternGreen = pattern.green;

	spi_tx_to_slave(&cmd, sizeof(cmd), sizeof(cmd.master), FP_SETLEDPATTERN_DELAY_US);
}

void fp_set_all_leds(enum led_state_t state, uint16_t delay) {
	fp_set_led(LED_OPERATION, state);
	delay_millis(delay);
	fp_set_led(LED_ERROR, state);
	delay_millis(delay);
	fp_set_led(LED_AUTOMATIC_SHUTDOWN, state);
	delay_millis(delay);
	fp_set_led(LED_TEMPERATURE, state);
	delay_millis(delay);
	fp_set_led(LED_PROTECTIVE_EARTH, state);
	delay_millis(delay);
	fp_set_led(LED_PHASE_ERROR, state);
	delay_millis(delay);
	fp_set_led(LED_OVERCURRENT, state);
	delay_millis(delay);
	fp_set_led(LED_AUTO_TRANSFORMER, state);
	delay_millis(delay);
	fp_set_led(LED_ISOLATION_TRANSFORMER, state);
	delay_millis(delay);
	fp_set_led(LED_OUTPUT, state);
	delay_millis(delay);
}

static void led_test_specific(enum fpEnum_ledIndex led) {
	fp_set_led(led, STATE_GREEN);
	delay_millis(500);
	fp_set_led(led, STATE_RED);
	delay_millis(500);
	fp_set_led(led, STATE_ORANGE);
	delay_millis(500);
	fp_set_led(led, STATE_OFF);
}

void fp_test_leds(void) {
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

struct btn_event_t fp_get_button_event(void) {
	struct fpCmd_ReadKeyboard cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_READKEYBOARD_CMDID;
	spi_tx_to_slave(&cmd, sizeof(cmd), sizeof(cmd.master), FP_READKEYBOARD_DELAY_US);

	struct btn_event_t returnValue;
	returnValue.eventType = cmd.slave.keyboardEvent;
	returnValue.key = cmd.slave.pressedKey;
	return returnValue;
}

void init_frontpanel(void) {
    fp_set_led(LED_OPERATION, STATE_OFF);
	fp_set_led(LED_ERROR, STATE_OFF);
	fp_set_led(LED_AUTOMATIC_SHUTDOWN, STATE_OFF);
	fp_set_led(LED_TEMPERATURE, STATE_OFF);
	fp_set_led(LED_PROTECTIVE_EARTH, STATE_OFF);
	fp_set_led(LED_PHASE_ERROR, STATE_OFF);
	fp_set_led(LED_OVERCURRENT, STATE_OFF);
	fp_set_led(LED_AUTO_TRANSFORMER, STATE_OFF);
	fp_set_led(LED_ISOLATION_TRANSFORMER, STATE_OFF);
	fp_set_led(LED_OUTPUT, STATE_OFF);
}
