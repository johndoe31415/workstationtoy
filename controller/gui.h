#ifndef __GUI_H__
#define __GUI_H__

#include <stdint.h>
#include <stdbool.h>

#define AUTOSHUTDOWN_TIMEOUT_SECONDS				(2 * 3600)
#define AUTOSHUTDOWN_TIMEOUT_GRACETIME_SECONDS		(1800)

enum uimode_t {
	MODE_BLINK_RANDOMLY
};

struct uistate_t {
	enum uimode_t ui_mode;
	uint16_t tick;
	uint32_t prng_state;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void ui_loop(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
