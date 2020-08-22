#ifndef __RELAYSWITCHER_H__
#define __RELAYSWITCHER_H__

enum SwitchState {
	SWST_PWR_OFF = 0,
	SWST_PWR_SELF_IDLE = 1,
	SWST_PWR_ON_IDLE = 2,
	SWST_ISO_OFF = 3,
	SWST_ISO_ON = 4,
	SWST_AUTO_OFF = 5,
	SWST_AUTO_ON = 6,
	SWST_ISOAUTO_OFF = 7,
	SWST_ISOAUTO_ON = 8,
	SWST_MAINS_OFF = 9,
	SWST_MAINS_ON = 10
};

#define RELAY(n)			(1 << ((n) - 1))

enum Relays {
	REL_PWRSELF = RELAY(1),
	REL_PWRSTATION = RELAY(2),
	REL_ISOENABLE = RELAY(3) | RELAY(12),
	REL_AUTOENABLE = RELAY(6),
	REL_AUTOSOURCESELECT = RELAY(4) | RELAY(5),
	REL_OUT1SOURCESELECT = RELAY(7) | RELAY(8),
	REL_OUT2SOURCESELECT = RELAY(9) | RELAY(10),
	REL_OUTPUTENABLE = RELAY(11),
};

// PWR_OFF <=> PWR_SELF_IDLE <=> PWR_ON_IDLE <=> SWST_ISO_OFF <=> SWST_ISO_ON
//                                           <=> SWST_AUTO_OFF <=> SWST_AUTO_ON
//                                           <=> SWST_ISOAUTO_OFF <=> SWST_ISOAUTO_ON
//                                           <=> SWST_MAINS_OFF <=> SWST_MAINS_ON


/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void relaySwitchState(enum SwitchState aTarget);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
