#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "delay.h"
#include "hal.h"
#include "rs232.h"
#include "spi.h"
#include "frontpanel.h"
#include "buzzer.h"
#include "gui.h"
#include "voltage.h"

int main(void) {
	initHAL();
	init_rs232();
	init_spi();
	init_buzzer();
	init_frontpanel();
	init_voltage();

	/* Then activate interrupts */
	sei();

	/* And enter GUI loop */
	ui_loop();

	while (true);
	return 0;
}
