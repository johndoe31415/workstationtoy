#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "delay.h"
#include "hal.h"
#include "rs232.h"
#include "spi.h"
#include "frontpanel.h"
#include "buzzer.h"
#include "gui.h"

static void set_relay_state(uint16_t value) {
	Rel1_SetConditional((value >> 0) & 1);
	Rel2_SetConditional((value >> 1) & 1);
	Rel3_SetConditional((value >> 2) & 1);
	Rel4_SetConditional((value >> 3) & 1);
	Rel5_SetConditional((value >> 4) & 1);
	Rel6_SetConditional((value >> 5) & 1);
	Rel7_SetConditional((value >> 6) & 1);
	Rel8_SetConditional((value >> 7) & 1);
	Rel9_SetConditional((value >> 8) & 1);
	Rel10_SetConditional((value >> 9) & 1);
	Rel11_SetConditional((value >> 10) & 1);
	Rel12_SetConditional((value >> 11) & 1);
	switch ((value >> 0) & 3) {
		case 0:	setLED(LED_OPERATION, STATE_OFF); break;
		case 1:	setLED(LED_OPERATION, STATE_RED); break;
		case 2:	setLED(LED_OPERATION, STATE_GREEN); break;
		case 3:	setLED(LED_OPERATION, STATE_ORANGE); break;
	}
	switch ((value >> 2) & 3) {
		case 0:	setLED(LED_ERROR, STATE_OFF); break;
		case 1:	setLED(LED_ERROR, STATE_RED); break;
		case 2:	setLED(LED_ERROR, STATE_GREEN); break;
		case 3:	setLED(LED_ERROR, STATE_ORANGE); break;
	}
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

int main(void) {
	initHAL();
	init_rs232();
	init_spi();
	init_buzzer();

	/* Then activate interrupts */
	sei();

	/* Enable "active" LED */
	setLED(LED_OPERATION, STATE_GREEN);

//	buzzer_play(BUZZER_NOTIFICATION);

	while (true) {
		/*
//		Voltmeter_Toggle();
		setLED(LED_OPERATION, STATE_RED);

			trip_rcd();
			*/
	}



#if 0
	set_relay_state(0xffff);
	delay_millis(1000);
	uint16_t x = 0xaaaa;
	while (true) {
		set_relay_state(x);
		bool lo = x & 1;
		x >>= 1;
		if (lo) {
			x = x ^ 58608;
		}
		delay_millis(100);
		/*
		for (uint16_t i = 3500; i < (1 << 12); i++) {
			set_relay_state(i);
			delay_millis(100);
		}
		*/
	}
#endif

//	buzzer_play(BUZZER_SIMPLE_ERROR);

	/* Enter GUI loop */
	guiLoop();

	while (true);
	return 0;
}
