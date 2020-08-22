#include <stdint.h>
#include <stdbool.h>

#include "AVRHeaders.h"
#include "RelaySwitcher.h"
#include "HAL.h"
#include "Delay.h"

#define RELAY_DISABLE_ALL

static const uint16_t switchOutputs[] PROGMEM = {
	[SWST_PWR_OFF]			= 0,
	[SWST_PWR_SELF_IDLE]	= REL_PWRSELF,
	[SWST_PWR_ON_IDLE]		= REL_PWRSELF | REL_PWRSTATION,
	[SWST_ISO_OFF]			= REL_PWRSELF | REL_PWRSTATION | REL_ISOENABLE | REL_OUT1SOURCESELECT,
	[SWST_ISO_ON]			= REL_PWRSELF | REL_PWRSTATION | REL_ISOENABLE | REL_OUT1SOURCESELECT | REL_OUTPUTENABLE,
	[SWST_AUTO_OFF]			= REL_PWRSELF | REL_PWRSTATION | REL_AUTOENABLE,
	[SWST_AUTO_ON]			= REL_PWRSELF | REL_PWRSTATION | REL_AUTOENABLE | REL_OUTPUTENABLE,
	[SWST_ISOAUTO_OFF]		= REL_PWRSELF | REL_PWRSTATION | REL_ISOENABLE | REL_AUTOSOURCESELECT,
	[SWST_ISOAUTO_ON]		= REL_PWRSELF | REL_PWRSTATION | REL_ISOENABLE | REL_AUTOSOURCESELECT | REL_OUTPUTENABLE,
	[SWST_MAINS_OFF]		= REL_PWRSELF | REL_PWRSTATION | REL_OUT2SOURCESELECT,
	[SWST_MAINS_ON]			= REL_PWRSELF | REL_PWRSTATION | REL_OUT2SOURCESELECT | REL_OUTPUTENABLE
};


static enum SwitchState currentState;

static void switchState(enum SwitchState aNewState) {
	emulationcallback(0, currentState, aNewState, (int)switchOutputs[currentState], (int)switchOutputs[aNewState]);

	uint16_t relayState;
	memcpy_P(&relayState, switchOutputs + aNewState, 2);
#ifndef RELAY_DISABLE_ALL
	Rel1_SetConditional(relayState & RELAY(1));
	Rel2_SetConditional(relayState & RELAY(2));
	Rel3_SetConditional(relayState & RELAY(3));
	Rel4_SetConditional(relayState & RELAY(4));
	Rel5_SetConditional(relayState & RELAY(5));
	Rel6_SetConditional(relayState & RELAY(6));
	Rel7_SetConditional(relayState & RELAY(7));
	Rel8_SetConditional(relayState & RELAY(8));
	Rel9_SetConditional(relayState & RELAY(9));
	Rel10_SetConditional(relayState & RELAY(10));
	Rel11_SetConditional(relayState & RELAY(11));
	Rel12_SetConditional(relayState & RELAY(12));
#endif
	delayMillis(50);
}

static void switchState_SWST_PWR_OFF(void) {
}

static void switchState_SWST_PWR_SELF_IDLE(void) {
}

static void switchState_SWST_PWR_ON_IDLE(void) {
}

static void switchState_SWST_ISO_OFF(void) {
}

static void switchState_SWST_ISO_ON(void) {
}

static void switchState_SWST_AUTO_OFF(void) {
}

static void switchState_SWST_AUTO_ON(void) {
}

static void switchState_SWST_ISOAUTO_OFF(void) {
}

static void switchState_SWST_ISOAUTO_ON(void) {
}

static void switchState_SWST_MAINS_OFF(void) {
}

static void switchState_SWST_MAINS_ON(void) {
}

void relaySwitchState(enum SwitchState aTarget) {
	while (currentState != aTarget) {
		switch (currentState) {
			case SWST_PWR_OFF:
				switchState(SWST_PWR_SELF_IDLE); switchState_SWST_PWR_SELF_IDLE(); currentState = SWST_PWR_SELF_IDLE;
				break;
			case SWST_PWR_SELF_IDLE:
				switch (aTarget) {
					case SWST_PWR_OFF: switchState(SWST_PWR_OFF); switchState_SWST_PWR_OFF(); currentState = SWST_PWR_OFF; break;
					default: switchState(SWST_PWR_ON_IDLE); switchState_SWST_PWR_ON_IDLE(); currentState = SWST_PWR_ON_IDLE; break;
				}
				break;
			case SWST_PWR_ON_IDLE:
				switch (aTarget) {
					case SWST_AUTO_OFF:
					case SWST_AUTO_ON:
						switchState(SWST_AUTO_OFF); switchState_SWST_AUTO_OFF(); currentState = SWST_AUTO_OFF; break;
					case SWST_ISOAUTO_ON:
					case SWST_ISOAUTO_OFF:
						switchState(SWST_ISOAUTO_OFF); switchState_SWST_ISOAUTO_OFF(); currentState = SWST_ISOAUTO_OFF; break;
					case SWST_ISO_ON:
					case SWST_ISO_OFF:
						switchState(SWST_ISO_OFF); switchState_SWST_ISO_OFF(); currentState = SWST_ISO_OFF; break;
					case SWST_MAINS_ON:
					case SWST_MAINS_OFF:
						switchState(SWST_MAINS_OFF); switchState_SWST_MAINS_OFF(); currentState = SWST_MAINS_OFF; break;
					default: switchState(SWST_PWR_SELF_IDLE); switchState_SWST_PWR_SELF_IDLE(); currentState = SWST_PWR_SELF_IDLE; break;
				}
				break;
			case SWST_ISO_OFF:
				switch (aTarget) {
					case SWST_ISO_ON: switchState(SWST_ISO_ON); switchState_SWST_ISO_ON(); currentState = SWST_ISO_ON; break;
					default: switchState(SWST_PWR_ON_IDLE); switchState_SWST_PWR_ON_IDLE(); currentState = SWST_PWR_ON_IDLE; break;
				}
				break;
			case SWST_ISO_ON:
				switchState(SWST_ISO_OFF); switchState_SWST_ISO_OFF(); currentState = SWST_ISO_OFF;
				break;
			case SWST_AUTO_OFF:
				switch (aTarget) {
					case SWST_AUTO_ON: switchState(SWST_AUTO_ON); switchState_SWST_AUTO_ON(); currentState = SWST_AUTO_ON; break;
					default: switchState(SWST_PWR_ON_IDLE); switchState_SWST_PWR_ON_IDLE(); currentState = SWST_PWR_ON_IDLE; break;
				}
				break;
			case SWST_AUTO_ON:
				switchState(SWST_AUTO_OFF); switchState_SWST_AUTO_OFF(); currentState = SWST_AUTO_OFF;
				break;
			case SWST_ISOAUTO_OFF:
				switch (aTarget) {
					case SWST_ISOAUTO_ON: switchState(SWST_ISOAUTO_ON); switchState_SWST_ISOAUTO_ON(); currentState = SWST_ISOAUTO_ON; break;
					default: switchState(SWST_PWR_ON_IDLE); switchState_SWST_PWR_ON_IDLE(); currentState = SWST_PWR_ON_IDLE; break;
				}
				break;
			case SWST_ISOAUTO_ON:
				switchState(SWST_ISOAUTO_OFF); switchState_SWST_ISOAUTO_OFF(); currentState = SWST_ISOAUTO_OFF;
				break;
			case SWST_MAINS_OFF:
				switch (aTarget) {
					case SWST_MAINS_ON: switchState(SWST_MAINS_ON); switchState_SWST_MAINS_ON(); currentState = SWST_MAINS_ON; break;
					default: switchState(SWST_PWR_ON_IDLE); switchState_SWST_PWR_ON_IDLE(); currentState = SWST_PWR_ON_IDLE; break;
				}
				break;
			case SWST_MAINS_ON:
				switchState(SWST_MAINS_OFF); switchState_SWST_MAINS_OFF(); currentState = SWST_MAINS_OFF;
				break;
			}
	}
}
