#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>
#include <stdbool.h>

#include "SPISlave.h"

#define MAX_KEYPRESS_COUNT				8

#define KEYBOARD_DEADTIME				10
#define KEYBOARD_THRESHOLD_SHORT		10
#define KEYBOARD_THRESHOLD_MED			30
#define KEYBOARD_THRESHOLD_LONG			80

struct KeyboardQueueEntry {
	enum fpEnum_keyboardEvent event;
	enum fpEnum_keyboardKey pressedKey;
};

struct keyState {
	bool fired;
	uint8_t counter;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
struct KeyboardQueueEntry getKeyboardRegister(void);
void keyboardTick(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
