#include <avr/interrupt.h>
#include <avr/io.h>

#include "LEDOutput.h"
#include "Keyboard.h"

static uint8_t counterMaxValue = 10;
static uint8_t counterValue = 0;

void setTimerMaxValue(uint8_t aNewTimerMaxValue) {
	if (aNewTimerMaxValue == 0) {
		return;
	}
	counterMaxValue = aNewTimerMaxValue;
	if (counterValue >= counterMaxValue) {
		counterValue = counterMaxValue / 2;
	}
}

uint8_t getTimerMaxValue(void) {
	return counterMaxValue;
}

ISR(TIMER0_OVF_vect) {
	TCNT0 = 0x64;
	counterValue++;
	if (counterValue >= counterMaxValue) {
		counterValue = 0;
		ledTick();
	}
	keyboardTick();
}

void initTimer(void) {
	TCCR0 = _BV(CS02) | _BV(CS00);		/* Clk / 1024 */
	TCNT0 = 0x64;						/* 10ms @ 16 MHz */
	TIMSK |= _BV(TOIE0);
}
