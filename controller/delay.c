#include <util/delay.h>

#include "delay.h"

void delayMillis(uint16_t aMillis) {
	while (aMillis--) {
		_delay_ms(1);
	}
}

/* Every count here takes about 1.376 µs */
void delayMicroseconds1376(uint16_t aMicros) {
	while (aMicros--) {
		_delay_us(1);
	}
}
