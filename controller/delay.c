#include <util/delay.h>

#include "delay.h"

void delay_millis(uint16_t milli_seconds) {
	while (milli_seconds--) {
		_delay_ms(1);
	}
}

/* Every count here takes about 1.376 µs */
void delay_1_376_us(uint16_t micro_seconds_1_376) {
	while (micro_seconds_1_376--) {
		_delay_us(1);
	}
}
