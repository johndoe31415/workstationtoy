#include <string.h>

#include "GUI.h"
#include "HAL.h"
#include "Frontpanel.h"
#include "RelaySwitcher.h"
#include "Delay.h"
#include "Buzzer.h"

static struct GUIState state;

static void handleKeypress(enum fpEnum_keyboardEvent aEventType, enum fpEnum_keyboardKey aKey) {
	if (aKey == KBD_KEY_OUTPUT) {
		if (state.outputState == OUTPUT_DISABLED) {
			if (aEventType == KBD_EVENT_PRESS_LONG) {
				state.outputState = OUTPUT_PERMANENTLY_ENABLED;
			} else {
				state.outputState = OUTPUT_ARMED;
			}
		} else {
			state.outputState = OUTPUT_DISABLED;
		}
	} else if (aKey == KBD_KEY_AUTO_TRANSFORMER) {
		state.autoEnabled = !state.autoEnabled;
		state.outputState = OUTPUT_DISABLED;
	} else if (aKey == KBD_KEY_ISOLATION_TRANSFORMER) {
		state.isoEnabled = !state.isoEnabled;
		state.outputState = OUTPUT_DISABLED;
	} else if (aKey == KBD_KEY_DEAD_MAN) {
		if (state.autoShutdownState == AUTOSHTDN_DISABLED) {
			state.autoShutdownState = AUTOSHTDN_IDLE;
		} else {
			if (aEventType == KBD_EVENT_PRESS_LONG) {
				state.autoShutdownState = AUTOSHTDN_DISABLED;
			}
		}
	}
	state.autoShutdownState = (state.autoShutdownState == AUTOSHTDN_DISABLED) ? AUTOSHTDN_DISABLED : AUTOSHTDN_IDLE;
	//state.lastUpdateTime = getTimeSeconds();
}

static bool handleFootpedal(bool aFootPedalState) {
	bool event = false;
	if (state.outputState == OUTPUT_ARMED) {
		if (aFootPedalState != state.footPedalState) {
			state.footPedalState = aFootPedalState;
			event = true;
		}
	}
	return event;
}

static void updateFrontpanelLEDs(void) {
	switch (state.outputState) {
		case OUTPUT_DISABLED:
			setLED(LED_OUTPUT, STATE_OFF);
			break;
		case OUTPUT_ARMED:
			if (state.footPedalState) {
				setLED(LED_OUTPUT, STATE_GREEN);
			} else {
				setLED(LED_OUTPUT, STATE_ORANGE);
			}
			break;
		case OUTPUT_PERMANENTLY_ENABLED:
			setLED(LED_OUTPUT, STATE_GREEN);
			break;
	}

	setLED(LED_ISOLATION_TRANSFORMER, state.isoEnabled ? STATE_GREEN : STATE_OFF);
	setLED(LED_AUTO_TRANSFORMER, state.autoEnabled ? STATE_GREEN : STATE_OFF);
	switch (state.autoShutdownState) {
		case AUTOSHTDN_IDLE:
			setLED(LED_AUTOMATIC_SHUTDOWN, STATE_OFF);
			break;
		case AUTOSHTDN_PENDING:
			setLED(LED_AUTOMATIC_SHUTDOWN, STATE_BLINK_ORANGE_SLOW);
			break;
		case AUTOSHTDN_DISABLED:
			setLED(LED_AUTOMATIC_SHUTDOWN, STATE_RED);
			break;
		case AUTOSHTDN_SHUTTINGDOWN:
			setLED(LED_AUTOMATIC_SHUTDOWN, STATE_BLINK_RED_FAST);
			break;
	}
}

static void updateStateMachine(void) {
	enum SwitchState currentState;
	currentState = SWST_PWR_ON_IDLE;

	if (state.autoShutdownState != AUTOSHTDN_SHUTTINGDOWN) {
		bool outputEnabled = (state.outputState == OUTPUT_PERMANENTLY_ENABLED) || ((state.outputState == OUTPUT_ARMED) && state.footPedalState);
		if (state.isoEnabled && state.autoEnabled) {
			currentState = outputEnabled ? SWST_ISOAUTO_ON : SWST_ISOAUTO_OFF;
		} else if (state.isoEnabled) {
			currentState = outputEnabled ? SWST_ISO_ON : SWST_ISO_OFF;
		} else if (state.autoEnabled) {
			currentState = outputEnabled ? SWST_AUTO_ON : SWST_AUTO_OFF;
		} else if (state.outputState != OUTPUT_DISABLED) {
			currentState = outputEnabled ? SWST_MAINS_ON : SWST_MAINS_OFF;
		}
	} else {
		currentState = SWST_PWR_OFF;
	}

	relaySwitchState(currentState);
}

void guiLoop(void) {
	memset(&state, 0, sizeof(state));
	state.outputState = OUTPUT_ARMED;	/* TODO REMOVEME */
	updateFrontpanelLEDs();
	updateStateMachine();
	while (true) {
		bool event = false;
		event = handleFootpedal(Footpedal_IsActive()) || event;

		if (Frontpanel_IRQ_IsActive()) {
			struct KeyboardEvent keyPressEvent = getFrontpanelKey();
			handleKeypress(keyPressEvent.eventType, keyPressEvent.key);
			//logmsg("Keypress type 0x%x, key 0x%x\r\n", keyPressEvent.eventType, keyPressEvent.key);
			event = true;
		}

		if (event) {
			updateFrontpanelLEDs();
			updateStateMachine();
		}

		delayMillis(10);
	}
}
