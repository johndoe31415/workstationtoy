#include "HAL.h"
#include "SPISlave.h"
#include "Keyboard.h"

static struct KeyboardQueueEntry keyboardQueue[MAX_KEYPRESS_COUNT];
static uint8_t keyboardQueueFill;
static uint8_t keyboardQueueWriteIndex;
static uint8_t keyboardQueueReadIndex;
static struct keyState keyStates[4];

static void pushNewKey(enum fpEnum_keyboardEvent aEvent, enum fpEnum_keyboardKey aPressedKey) {
	if (keyboardQueueFill < MAX_KEYPRESS_COUNT) {
		keyboardQueue[keyboardQueueWriteIndex].event = aEvent;
		keyboardQueue[keyboardQueueWriteIndex].pressedKey = aPressedKey;
		keyboardQueueWriteIndex = (keyboardQueueWriteIndex + 1) % MAX_KEYPRESS_COUNT;
		keyboardQueueFill++;
		SignalIRQ_SetActive();
	}
}

struct KeyboardQueueEntry getKeyboardRegister(void) {
	struct KeyboardQueueEntry entry;
	if (keyboardQueueFill == 0) {
		entry.event = KBD_EVENT_NONE;
		entry.pressedKey = KBD_KEY_NONE;
	} else {
		entry = keyboardQueue[keyboardQueueReadIndex];
		keyboardQueueReadIndex = (keyboardQueueReadIndex + 1) % MAX_KEYPRESS_COUNT;
		keyboardQueueFill--;
		if (keyboardQueueFill == 0) {
			SignalIRQ_SetInactive();
		}
	}
	return entry;
}

static void processKeyState(uint8_t aKeyIndex, bool aCurrentButtonState) {
	struct keyState *state = keyStates + aKeyIndex;

	if (state->fired) {
		/* Key is currently in deadtime mode */
		if (!aCurrentButtonState) {
			state->counter--;
			if (state->counter == 0) {
				state->fired = false;
			}
		}
	} else {
		if (aCurrentButtonState) {
			/* Button is pressed */
			state->counter++;
			if (state->counter >= KEYBOARD_THRESHOLD_LONG) {
				pushNewKey(KBD_EVENT_PRESS_LONG, aKeyIndex);
				state->fired = true;
				state->counter = KEYBOARD_DEADTIME;
			}
		} else {
			/* Button is released, either fire */
			if (state->counter < KEYBOARD_THRESHOLD_SHORT) {
				if (state->counter > 0) {
					state->counter--;
				}
			} else {
				/* Some valid key press has occured */
				if (state->counter >= KEYBOARD_THRESHOLD_LONG) {
					pushNewKey(KBD_EVENT_PRESS_LONG, aKeyIndex);
				} else if (state->counter >= KEYBOARD_THRESHOLD_MED) {
					pushNewKey(KBD_EVENT_PRESS_MEDIUM, aKeyIndex);
				} else {
					pushNewKey(KBD_EVENT_PRESS_SHORT, aKeyIndex);
				}
								
				state->fired = true;
				state->counter = KEYBOARD_DEADTIME;
			}
		}
	}
}

void keyboardTick(void) {
	processKeyState(KBD_KEY_DEAD_MAN, Key_Deadman_IsActive());
	processKeyState(KBD_KEY_AUTO_TRANSFORMER, Key_AutoXfrm_IsActive());
	processKeyState(KBD_KEY_ISOLATION_TRANSFORMER, Key_IsoXfrm_IsActive());
	processKeyState(KBD_KEY_OUTPUT, Key_Output_IsActive());
}

