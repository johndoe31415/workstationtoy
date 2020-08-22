#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ADC.h"
#include "Delay.h"
#include "HAL.h"
#include "RS232.h"
#include "SPISlave.h"

int main() {
	initHAL();
//	initRs232();
	initADC();
	spiSlaveInit();
	sei();


	while (true) {
		checkSPIForReset();
		delayMicroseconds(500);
	}
	
	return 0;
}
