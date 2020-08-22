#include <avr/io.h>
#include <avr/interrupt.h>

#include "SignalProcessing.h"
#include "HAL.h"

ISR(TIMER0_OVF_vect) {
	/* Clear Timer0 overflow interrupt flag */
	TCNT0 = 0x7e;		/* 16 MHz / 256, reload 0x7e -> 479 Hz (no integer multiple of 50 Hz!) */
}

ISR(ADC_vect) {
	nextSample(ADC);
}

void initADC(void) {
	ADMUX = 0;																				// Ref = AREF, Mux = ADC0
	ADCSRB = _BV(ADTS2);																	// Auto trigger source: Timer0 overflow
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADATE) | _BV(ADIE);		// Divider = 1 / 128 (125 kHz), Auto trigger armed, IRQ enabled
	
	TCCR0B = _BV(CS02);		// Timer 0 prescaler 1/256
	TIMSK0 = _BV(TOIE0);
}
