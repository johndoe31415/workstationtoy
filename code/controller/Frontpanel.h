#ifndef __FRONTPANEL_H__
#define __FRONTPANEL_H__

#include <stdint.h>

#include "../frontpanel/SPISlave.h"

enum FrontpanelLEDState {
	STATE_OFF = 0,
	STATE_GREEN = 1,
	STATE_RED = 2,
	STATE_ORANGE = 3,
	STATE_BLINK_ORANGE_SLOW = 4,
	STATE_BLINK_RED_FAST = 5,
};

struct KeyboardEvent {
	enum fpEnum_keyboardEvent eventType:4;
	enum fpEnum_keyboardKey key:4;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void setLED(enum fpEnum_ledIndex aLED, enum FrontpanelLEDState aState);
void ledTest(void);
struct KeyboardEvent getFrontpanelKey(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
