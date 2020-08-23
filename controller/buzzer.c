#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "delay.h"
#include "buzzer.h"

#define UINT32(x)							((uint32_t)(x))
#define ROUNDDIV(a, b)						(((a) + ((b) / 2)) / (b))
#define FREQUENCY(f)						ROUNDDIV(125000UL, UINT32(f))
#define LENGTH(f, l)						ROUNDDIV(UINT32(f) * UINT32(l) * 2, 1000UL)

struct tone {
	uint8_t frequency;
	uint16_t length;
};

struct melody {
	uint8_t repeat;
	uint8_t toneCount;
	struct tone tones[];
};

static uint8_t currentTone;
static uint8_t currentRepetition;
static uint16_t currentLength;
static const struct melody *currentSound;

#define PAUSE(lmillis)						{ .frequency = 0, .length = LENGTH(1000, lmillis) }
#define NOTE(f, lmillis)					{ .frequency = FREQUENCY(f), .length = LENGTH(f, lmillis) }

static const struct melody tcasAlert PROGMEM = {
	.repeat = 4,
	.toneCount = 10,
	.tones = {
		NOTE(1600, 60),
		PAUSE(20),
		NOTE(1600, 60),
		PAUSE(20),
		NOTE(1600, 60),
		PAUSE(20),
		NOTE(1600, 60),
		PAUSE(20),
		NOTE(1600, 60),
		PAUSE(80),
	},
};

static const struct melody simpleError PROGMEM = {
	.repeat = 4,
	.toneCount = 4,
	.tones = {
		NOTE(800, 60),
		PAUSE(20),
		NOTE(490, 60),
		PAUSE(20),
	},
};

static const struct melody notificationMelody PROGMEM = {
	.repeat = 2,
	.toneCount = 2,
	.tones = {
		NOTE(1200, 80),
		PAUSE(80),
	},
};

static const struct melody* const melodies[] PROGMEM = {
	[BUZZER_CRITICAL_ERROR] = &tcasAlert,
	[BUZZER_SIMPLE_ERROR] = &simpleError,
	[BUZZER_NOTIFICATION] = &notificationMelody,
};

static void buzzerOff(void) {
	TCCR0A &= ~(_BV(COM0A0) | _BV(COM0A1) | _BV(CS00) | _BV(CS01) | _BV(CS02));
}

static void buzzerOnSilent(void) {
	TCCR0A = (TCCR0A | _BV(CS01) | _BV(CS00)) & ~(_BV(COM0A0) | _BV(COM0A1));

}

static void buzzerOn(void) {
	TCCR0A |= _BV(COM0A0) | _BV(CS01) | _BV(CS00);
}

static void nextNote(void) {
	if (!currentSound) {
		return;
	}

	struct melody melody;
	memcpy_P(&melody, currentSound, sizeof(struct melody));

	if (currentTone == melody.toneCount) {
		currentTone = 0;
		/* End of current melody */
		if (melody.repeat > 0) {
			currentRepetition++;
			if (currentRepetition == melody.repeat) {
				/* End of repetitions */
				buzzerOff();
				currentSound = NULL;
				return;
			}
		}
	}

	struct tone tone;
	memcpy_P(&tone, &currentSound->tones[currentTone], sizeof(struct tone));

	if (tone.frequency == 0) {
		OCR0A = 125;
		currentLength = tone.length;
		buzzerOnSilent();
	} else {
		OCR0A = tone.frequency;
		currentLength = tone.length;
		buzzerOn();
	}

	currentTone++;
}

void buzzerPlay(enum BuzzerMelody aTone) {
	memcpy_P(&currentSound, melodies + aTone, sizeof(const struct melody*));
	currentTone = 0;
	currentRepetition = 0;
	currentLength = 0;
	nextNote();
}

ISR(TIMER0_COMP_vect) {
	if (currentLength > 0) {
		currentLength--;
	} else {
		nextNote();
	}
}

void initBuzzer(void) {
	TCCR0A = _BV(WGM01);		/* Generate PWM */
	TIMSK0 = _BV(OCF0A);		/* Interrupt on compare */
	(void)buzzerOn;
}

