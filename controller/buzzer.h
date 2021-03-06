#ifndef __BUZZER_H__
#define __BUZZER_H__

enum buzzer_melody_t {
	BUZZER_CRITICAL_ERROR = 0,
	BUZZER_SIMPLE_ERROR = 1,
	BUZZER_NOTIFICATION = 2,
	BUZZER_EMERGENCY = 3,
	BUZZER_PHASOR,
	BUZZER_WHISTLE,
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void buzzer_play(enum buzzer_melody_t melody);
void init_buzzer(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
