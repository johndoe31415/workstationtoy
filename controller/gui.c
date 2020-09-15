#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "gui.h"
#include "hal.h"
#include "frontpanel.h"
#include "delay.h"
#include "buzzer.h"
#include "voltage.h"
#include "debounce.h"

static struct uistate_t state;

static void set_relay_state(uint16_t value, uint16_t delay) {
	Rel1_SetConditional((value >> 0) & 1);
	delay_millis(delay);
	Rel2_SetConditional((value >> 1) & 1);
	delay_millis(delay);
	Rel3_SetConditional((value >> 2) & 1);
	delay_millis(delay);
	Rel4_SetConditional((value >> 3) & 1);
	delay_millis(delay);
	Rel5_SetConditional((value >> 4) & 1);
	delay_millis(delay);
	Rel6_SetConditional((value >> 5) & 1);
	delay_millis(delay);
	Rel7_SetConditional((value >> 6) & 1);
	delay_millis(delay);
	Rel8_SetConditional((value >> 7) & 1);
	delay_millis(delay);
	Rel9_SetConditional((value >> 8) & 1);
	delay_millis(delay);
	Rel10_SetConditional((value >> 9) & 1);
	delay_millis(delay);
	Rel11_SetConditional((value >> 10) & 1);
	delay_millis(delay);
	Rel12_SetConditional((value >> 11) & 1);
	delay_millis(delay);
}

static void set_led_state(uint32_t value, uint16_t delay) {
	fp_set_led(LED_OPERATION, (value >> 0) & 3);
	delay_millis(delay);
	fp_set_led(LED_ERROR, (value >> 2) & 3);
	delay_millis(delay);
	fp_set_led(LED_AUTOMATIC_SHUTDOWN, (value >> 4) & 3);
	delay_millis(delay);
	fp_set_led(LED_TEMPERATURE, (value >> 6) & 3);
	delay_millis(delay);
	fp_set_led(LED_PROTECTIVE_EARTH, (value >> 8) & 3);
	delay_millis(delay);
	fp_set_led(LED_PHASE_ERROR, (value >> 10) & 3);
	delay_millis(delay);
	fp_set_led(LED_OVERCURRENT, (value >> 12) & 3);
	delay_millis(delay);
	fp_set_led(LED_AUTO_TRANSFORMER, (value >> 14) & 3);
	delay_millis(delay);
	fp_set_led(LED_ISOLATION_TRANSFORMER, (value >> 16) & 3);
	delay_millis(delay);
	fp_set_led(LED_OUTPUT, (value >> 18) & 3);
	delay_millis(delay);
}

static uint32_t xorshift_next(void) {
	state.prng_state ^= state.prng_state << 13;
	state.prng_state ^= state.prng_state >> 17;
	state.prng_state ^= state.prng_state << 5;
	return state.prng_state;
}

static void trip_rcd(void) {
	TripRCD1_SetInactive();
	TripRCD2_SetActive();
	delay_millis(100);
	TripRCD1_SetActive();
	TripRCD2_SetInactive();
	delay_millis(100);
	TripRCD1_SetInactive();
}


static void handle_keypress(enum fpEnum_keyboardEvent event_type, enum fpEnum_keyboardKey key) {
	if (key == KBD_KEY_OUTPUT) {
		switch (state.ui_mode) {
			case MODE_BLINK_RANDOMLY:
				state.speed++;
				if (state.speed > 5) {
					state.speed = 0;
				}
				break;

			case MODE_RELAY_TICKER:
				state.relay_count = xorshift_next();
				break;

			case MODE_INVALID: break;
		}
	} else if (key == KBD_KEY_AUTO_TRANSFORMER) {
		buzzer_play(BUZZER_CRITICAL_ERROR);
	} else if (key == KBD_KEY_ISOLATION_TRANSFORMER) {
		buzzer_play(BUZZER_NOTIFICATION);
	} else if (key == KBD_KEY_DEAD_MAN) {
		state.ui_mode++;
		if (state.ui_mode == MODE_INVALID) {
			state.ui_mode = MODE_BLINK_RANDOMLY;
		}
	}
}

static void clear_keypresses(void) {
	struct btn_event_t button;
	do {
		button = fp_get_button_event();
	} while (button.eventType != KBD_EVENT_NONE);
}

static void init_ui(void) {
	buzzer_play(BUZZER_NOTIFICATION);
	set_relay_state(0, 0);
	fp_set_all_leds(STATE_OFF, 0);
	fp_set_all_leds(STATE_GREEN, 50);
	set_relay_state(0xffff, 40);
	fp_set_all_leds(STATE_RED, 50);
	fp_set_all_leds(STATE_ORANGE, 50);
	fp_set_all_leds(STATE_OFF, 0);
	set_relay_state(0, 40);
	buzzer_play(BUZZER_SIMPLE_ERROR);
}

static void ui_tick_blink_randomly(void) {
	uint16_t threshold = 100;
	if (state.speed == 1) {
		threshold = 50;
	} else if (state.speed == 2) {
		threshold = 25;
	} else if (state.speed == 3) {
		threshold = 10;
	} else if (state.speed == 4) {
		threshold = 5;
	}

	if (state.tick < threshold) {
		return;
	}

	state.tick = 0;
	uint32_t rng = xorshift_next();
	set_led_state(rng, 0);
}

static void ui_tick_relay_ticker(void) {
	if (state.tick < 30) {
		return;
	}

	state.tick = 0;
	state.relay_count++;
	set_led_state(state.relay_count, 0);
	set_relay_state(state.relay_count, 0);
}

static void ui_tick(void) {
	switch (state.ui_mode) {
		case MODE_BLINK_RANDOMLY: ui_tick_blink_randomly(); break;
		case MODE_RELAY_TICKER: ui_tick_relay_ticker(); break;
		case MODE_INVALID: break;
	}
}

static void rotary_read(void) {
	if (Rotary_IsActive()) {
		state.voltage += 3;
		if (state.voltage >= 512) {
			state.voltage = 0;
			trip_rcd();
		}
		set_voltage(state.voltage);
	}
}

static void button_on(void) {
	buzzer_play(BUZZER_PHASOR);
}

static void button_off(void) {
	buzzer_play(BUZZER_WHISTLE);
	uint32_t value = 1;
	for (int i = 0; i < 10; i++) {
		set_led_state(value, 0);
		delay_millis(50);
		value <<= 2;
	}
}

static void button_emergency_off(void) {
	fp_set_all_leds(STATE_GREEN, 0);
	buzzer_play(BUZZER_EMERGENCY);
	fp_set_all_leds(STATE_BLINK_RED_MEDIUM, 300);
	delay_millis(2000);
}

static void buttons_read(void) {
	static struct debounce_t debounce_on, debounce_off, debounce_emergency;
	if (debounce(&debounce_on, Switch_On_IsActive()) == ACTION_PRESSED) {
		button_on();
	}
	if (debounce(&debounce_off, Switch_Off_IsActive()) == ACTION_PRESSED) {
		button_off();
	}
	if (debounce(&debounce_emergency, Switch_EmergencyOff_IsActive()) == ACTION_PRESSED) {
		button_emergency_off();
	}
}

void ui_loop(void) {
	clear_keypresses();
	init_ui();

	memset(&state, 0, sizeof(state));
	state.ui_mode = MODE_BLINK_RANDOMLY;
	state.prng_state = 0xc32675e4UL;

	while (true) {
		if (Frontpanel_IRQ_IsActive()) {
			struct btn_event_t keyPressEvent = fp_get_button_event();
			handle_keypress(keyPressEvent.eventType, keyPressEvent.key);
			//printf_P(PSTR("Keypress type 0x%x, key 0x%x\r\n"), keyPressEvent.eventType, keyPressEvent.key);
		}

		state.tick++;
		ui_tick();
		rotary_read();
		buttons_read();
		delay_millis(10);
	}
}
