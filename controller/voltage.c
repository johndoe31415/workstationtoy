#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "voltage.h"

void set_voltage(uint16_t value) {
	if (value > 511) {
		value = 511;
	}
	OCR1A = value;
}

void init_voltage(void) {
	TCCR1A = _BV(WGM11) | _BV(COM1A1);		/* Generate PWM */
	TCCR1B = _BV(CS12);
}
