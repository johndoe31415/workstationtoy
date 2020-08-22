#ifndef __BUZZER_H__
#define __BUZZER_H__

enum BuzzerMelody {
	BUZZER_CRITICAL_ERROR = 0,
	BUZZER_SIMPLE_ERROR = 1,
	BUZZER_NOTIFICATION = 2,
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void buzzerPlay(enum BuzzerMelody aTone);
void initBuzzer(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
