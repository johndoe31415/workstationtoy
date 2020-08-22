#include <stdio.h>
#include <stdarg.h>

#include <avr/interrupt.h>

#include "Debug.h"
#include "Delay.h"

void logmsg_P(const char *aMessage, ...) {
	/* Print time */
	struct time t;
	getTime(&t);

	uint8_t irqFlagRegister;
	irqFlagRegister = SREG;
	cli();

	timekeeperStrbuf timeStr;
	formatTime(&t, timeStr);
	mprintf("%s: ", timeStr);

	/* Then print message */
	va_list varArgs;
	va_start(varArgs, aMessage);
	vfprintf_P(stdout, aMessage, varArgs);
	va_end(varArgs);

	SREG = irqFlagRegister;
}

void softassertionFail(const char *aMessage, const char *aFile, uint16_t aLine) {
	cli();
	while (true) {
		mprintf("Soft assertion fail: %S (%S:%d)\r\n", aMessage, aFile, aLine);
		delayMillis(1000);
	}
}
