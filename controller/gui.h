#ifndef __GUI_H__
#define __GUI_H__

#include <stdint.h>
#include <stdbool.h>

enum uimode_t {
	MODE_BLINK_RANDOMLY,
	MODE_RELAY_TICKER,
	MODE_INVALID,
};

struct uistate_t {
	enum uimode_t ui_mode;
	uint16_t voltage;
	uint16_t tick;
	uint8_t speed;
	uint32_t prng_state;
	uint32_t relay_count;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void ui_loop(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
