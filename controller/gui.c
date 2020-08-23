#include <string.h>

#include "gui.h"
#include "hal.h"
#include "frontpanel.h"
#include "delay.h"
#include "buzzer.h"

static struct uistate_t state;

static void handleKeypress(enum fpEnum_keyboardEvent aEventType, enum fpEnum_keyboardKey aKey) {
	if (aKey == KBD_KEY_OUTPUT) {
	} else if (aKey == KBD_KEY_AUTO_TRANSFORMER) {
	} else if (aKey == KBD_KEY_ISOLATION_TRANSFORMER) {
	} else if (aKey == KBD_KEY_DEAD_MAN) {
	}
}

void guiLoop(void) {
	memset(&state, 0, sizeof(state));
	while (true) {
		bool event = false;

		if (Frontpanel_IRQ_IsActive()) {
			struct KeyboardEvent keyPressEvent = getFrontpanelKey();
			handleKeypress(keyPressEvent.eventType, keyPressEvent.key);
			//logmsg("Keypress type 0x%x, key 0x%x\r\n", keyPressEvent.eventType, keyPressEvent.key);
			event = true;

			setLED(LED_PROTECTIVE_EARTH, STATE_BLINK_ORANGE_SLOW);
		}

		if (event) {
		}

		delay_millis(10);
	}
}
