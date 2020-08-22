#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Delay.h"
#include "HAL.h"
#include "Debug.h"
#include "RS232.h"
#include "TimeKeeper.h"
#include "IntegrityCheck.h"
#include "SPI.h"
#include "Frontpanel.h"
#include "Panic.h"
#include "Buzzer.h"
#include "RelaySwitcher.h"
#include "GUI.h"

int main() {
	initHAL();
	initRs232();
	initTimekeeper();
	initSPI();
	initBuzzer();

	logmsg("Device reset\r\n");

	/* Check integrity of EEPROM and flash itself */
	flashIntegrityCheck();
	logmsg("EEPROM and Flash memory of main unit intact.\r\n");

	/* Then activate interrupts */
	sei();

	/* Set self power and activate station */
	relaySwitchState(SWST_PWR_ON_IDLE);

	/* Enable "active" LED */
	setLED(LED_OPERATION, STATE_GREEN);

	/* Enter GUI loop */
	guiLoop();

	while (true);
	return 0;
}
