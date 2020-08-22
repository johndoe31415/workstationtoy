#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Delay.h"
#include "HAL.h"

uint16_t getMonitorStates(void) {
	/*
	uint16_t state = 0;
	state |= Sense01_IsActive() ? (1 << 0) : 0;
	state |= Sense02_IsActive() ? (1 << 1) : 0;
	state |= Sense03_IsActive() ? (1 << 2) : 0;
	state |= Sense04_IsActive() ? (1 << 3) : 0;
	state |= Sense05_IsActive() ? (1 << 4) : 0;
	state |= Sense06_IsActive() ? (1 << 5) : 0;
	state |= Sense07_IsActive() ? (1 << 6) : 0;
	state |= Sense08_IsActive() ? (1 << 7) : 0;
	state |= Sense09_IsActive() ? (1 << 8) : 0;
	state |= Sense10_IsActive() ? (1 << 9) : 0;
	state |= Sense11_IsActive() ? (1 << 10) : 0;
	state |= Sense12_IsActive() ? (1 << 11) : 0;
	return state;
	*/
	return (PINC & 0x3f) | ((PIND & 0x3f) << 6);
}

uint8_t getMonitorStateNo(void) {
	if (Sense01_IsActive()) return 1;
	if (Sense02_IsActive()) return 2;
	if (Sense03_IsActive()) return 3;
	if (Sense04_IsActive()) return 4;
	if (Sense05_IsActive()) return 5;
	if (Sense06_IsActive()) return 6;
	if (Sense07_IsActive()) return 7;
	if (Sense08_IsActive()) return 8;
	if (Sense09_IsActive()) return 9;
	if (Sense10_IsActive()) return 10;
	if (Sense11_IsActive()) return 11;
	if (Sense12_IsActive()) return 12;
	return 0;
}

void blinkLED(uint8_t count) {
	uint8_t i;
	for (i = 0; i < count; i++) {
		LEDRed_SetActive();
		delayMillis(100);
		LEDRed_SetInactive();
		delayMillis(300);
	}
}

void loopCheck() {
	while (true) {
		uint8_t state = getMonitorStateNo();
		if (state == 0) {
			LEDRed_SetInactive();
		} else {
			blinkLED(state);
			delayMillis(1000);
		}
	}
}

int main() {
	initHAL();
	sei();

	loopCheck();

	while (true) {
#if 0
		if (SS_IsActive()) {
			while (SS_IsActive());
			spiReset();
		}
#endif
	}
	
	return 0;
}
