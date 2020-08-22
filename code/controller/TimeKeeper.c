#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "TimeKeeper.h"

static uint32_t seconds;

void getTime(struct time *aTime) {
	TIMSK2 &= ~_BV(TOIE2);
	aTime->fraction = TCNT2;
	aTime->seconds = seconds;
	TIMSK2 |= _BV(TOIE2);
}

uint32_t getTimeSeconds(void) {
	return seconds;
}

void timeDiff(struct time *aTime) {
	struct time now;
	getTime(&now);
	aTime->seconds = now.seconds - aTime->seconds;
	if (now.fraction >= aTime->fraction) {
		aTime->fraction = now.fraction - aTime->fraction;
	} else {
		aTime->fraction = now.fraction - aTime->fraction;
		aTime->seconds -= 1;
	}
}

void formatTime(const struct time *aTime, timekeeperStrbuf aBuffer) {
	snprintf(aBuffer, sizeof(timekeeperStrbuf), "%5lu.%03d", aTime->seconds, aTime->fraction * 125 / 32);
}

ISR(TIMER2_OVF_vect) {
	seconds++;
}

void disableTimekeeper(void) {
	TCCR2A = 0;
}

void initTimekeeper(void) {
	ASSR |= _BV(AS2);
	TCCR2A |= _BV(CS22) | _BV(CS20);
	TIMSK2 |= _BV(TOIE2);
}
