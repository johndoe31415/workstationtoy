#ifndef __GUI_H__
#define __GUI_H__

#include <stdint.h>
#include <stdbool.h>

#define AUTOSHUTDOWN_TIMEOUT_SECONDS				(2 * 3600)
#define AUTOSHUTDOWN_TIMEOUT_GRACETIME_SECONDS		(1800)

enum outputState {
	OUTPUT_DISABLED = 0,
	OUTPUT_ARMED = 1,
	OUTPUT_PERMANENTLY_ENABLED = 2
};

enum autoShutdownState {
	AUTOSHTDN_IDLE = 0,
	AUTOSHTDN_DISABLED = 1,
	AUTOSHTDN_PENDING = 2,
	AUTOSHTDN_SHUTTINGDOWN = 3
};

struct GUIState {
	bool isoEnabled;
	bool autoEnabled;
	enum outputState outputState;
	enum autoShutdownState autoShutdownState;
	uint32_t lastUpdateTime;
	bool footPedalState;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void guiLoop(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
