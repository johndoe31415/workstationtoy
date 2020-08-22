#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Delay.h"
#include "HAL.h"
#include "LEDOutput.h"
#include "SPISlave.h"
#include "Timer.h"

int main() {
	initHAL();
	ledInit();
	spiSlaveInit();
	initTimer();
	sei();

	while (true) {
		checkSPIForReset();
		delayMicroseconds(500);
	}
	
	return 0;
}
