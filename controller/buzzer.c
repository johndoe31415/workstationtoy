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

struct tone_t {
	uint8_t frequency;
	uint16_t length;
};

struct melody_t {
	uint8_t repeat;
	uint8_t toneCount;
	struct tone_t tones[];
};

static uint8_t current_tone;
static uint8_t current_repetition;
static uint16_t current_length;
static const struct melody_t *current_sound;

#define PAUSE(lmillis)						{ .frequency = 0, .length = LENGTH(1000, lmillis) }
#define NOTE(f, lmillis)					{ .frequency = FREQUENCY(f), .length = LENGTH(f, lmillis) }

static const struct melody_t tcas_alert PROGMEM = {
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

static const struct melody_t simple_error PROGMEM = {
	.repeat = 4,
	.toneCount = 4,
	.tones = {
		NOTE(800, 60),
		PAUSE(20),
		NOTE(490, 60),
		PAUSE(20),
	},
};

static const struct melody_t notificationMelody PROGMEM = {
	.repeat = 2,
	.toneCount = 2,
	.tones = {
		NOTE(1200, 80),
		PAUSE(80),
	},
};

static const struct melody_t* const melodies[] PROGMEM = {
	[BUZZER_CRITICAL_ERROR] = &tcas_alert,
	[BUZZER_SIMPLE_ERROR] = &simple_error,
	[BUZZER_NOTIFICATION] = &notificationMelody,
};

static void buzzer_off(void) {
	TCCR0A &= ~(_BV(COM0A0) | _BV(COM0A1) | _BV(CS00) | _BV(CS01) | _BV(CS02));
}

static void buzzer_on_silent(void) {
	TCCR0A = (TCCR0A | _BV(CS01) | _BV(CS00)) & ~(_BV(COM0A0) | _BV(COM0A1));

}

static void buzzer_on(void) {
	TCCR0A |= _BV(COM0A0) | _BV(CS01) | _BV(CS00);
}

static void nextNote(void) {
	if (!current_sound) {
		return;
	}

	struct melody_t melody;
	memcpy_P(&melody, current_sound, sizeof(struct melody_t));

	if (current_tone == melody.toneCount) {
		current_tone = 0;
		/* End of current melody */
		if (melody.repeat > 0) {
			current_repetition++;
			if (current_repetition == melody.repeat) {
				/* End of repetitions */
				buzzer_off();
				current_sound = NULL;
				return;
			}
		}
	}

	struct tone_t tone;
	memcpy_P(&tone, &current_sound->tones[current_tone], sizeof(struct tone_t));

	if (tone.frequency == 0) {
		OCR0A = 125;
		current_length = tone.length;
		buzzer_on_silent();
	} else {
		OCR0A = tone.frequency;
		current_length = tone.length;
		buzzer_on();
	}

	current_tone++;
}

void buzzer_play(enum buzzer_melody_t aTone) {
	memcpy_P(&current_sound, melodies + aTone, sizeof(const struct melody_t*));
	current_tone = 0;
	current_repetition = 0;
	current_length = 0;
	nextNote();
}

ISR(TIMER0_COMP_vect) {
	if (current_length > 0) {
		current_length--;
	} else {
		nextNote();
	}
}

void init_buzzer(void) {
	TCCR0A = _BV(WGM01);		/* Generate PWM */
	TIMSK0 = _BV(OCF0A);		/* Interrupt on compare */
	(void)buzzer_on;
}

