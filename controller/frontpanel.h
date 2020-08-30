#ifndef __FRONTPANEL_H__
#define __FRONTPANEL_H__

#include <stdint.h>

#include "../frontpanel/SPISlave.h"

enum led_state_t {
	STATE_OFF = 0,
	STATE_GREEN = 1,
	STATE_RED = 2,
	STATE_ORANGE = 3,
	STATE_BLINK_ORANGE_SLOW = 4,
	STATE_BLINK_RED_FAST = 5,
};

struct btn_event_t {
	enum fpEnum_keyboardEvent eventType:4;
	enum fpEnum_keyboardKey key:4;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void fp_set_led(enum fpEnum_ledIndex led, enum led_state_t state);
void fp_set_all_leds(enum led_state_t state, uint16_t delay);
void fp_test_leds(void);
struct btn_event_t fp_get_button_event(void);
void init_frontpanel(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
