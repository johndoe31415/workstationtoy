#include <stdint.h>
#include <stdbool.h>

#include <avr/interrupt.h>

#include "Errors.h"
#include "Debug.h"
#include "Delay.h"
#include "SPI.h"
#include "Frontpanel.h"
#include "TimeKeeper.h"

void invokePanic(const char *aMessage, const char *aFile, uint16_t aLine, enum resultCode aPanicReason) {
	disableTimekeeper();
	cli();
	spiDeselect();
	delayMillis(25);

	setLED(LED_ERROR, STATE_BLINK_RED_FAST);
	while (true) {
		if (aMessage == NULL) {
			logmsg("Panic code %u: %S (%S, %S:%d)\r\n", aPanicReason, getErrorString(aPanicReason), getErrorSymbolName(aPanicReason), aFile, aLine);
		} else {
			logmsg("Panic code %u: %S (%S, %S, %S:%d)\r\n", aPanicReason, aMessage, getErrorString(aPanicReason), getErrorSymbolName(aPanicReason), aFile, aLine);
		}
		for (int8_t bit = 3; bit >= 0; bit--) {
			bool bitValue;
			bitValue = ((1 << bit) & aPanicReason) != 0;

			setLED(LED_OPERATION, bitValue ? STATE_GREEN : STATE_RED);
			delayMillis(500);

			setLED(LED_OPERATION, STATE_OFF);
			delayMillis(150);
		}
		delayMillis(1000);
	}
}
