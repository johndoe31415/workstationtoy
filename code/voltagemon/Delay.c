#include <util/delay.h>

#include "Delay.h"

void delayMillis(uint16_t aMillis) {
	while (aMillis--) {
		_delay_ms(1);
	}
}
