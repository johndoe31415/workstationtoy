#include <stdio.h>
#include <stdarg.h>

#include "RelaySwitcher.h"

static void checkxorbit(int aXorValue, int aNewState, const char *aBitName, int aBitValue) {
	if ((aXorValue & aBitValue) != 0) {
		fprintf(stderr, "   %c %s\n", (aNewState & aBitValue) ? '+' : '-', aBitName);
	}
}

static void callbackStateSwitch(enum SwitchState aOld, enum SwitchState aNew, int aOutOld, int aOutNew) {
	int xor = aOutOld ^ aOutNew;
	fprintf(stderr, "switchState %d -> %d relay 0x%x -> 0x%x (XOR 0x%x)\n", aOld, aNew, aOutOld, aOutNew, xor);
	checkxorbit(xor, aOutNew, "REL_PWRSTATION", REL_PWRSTATION);
	checkxorbit(xor, aOutNew, "REL_ISOENABLE", REL_ISOENABLE);
	checkxorbit(xor, aOutNew, "REL_AUTOENABLE", REL_AUTOENABLE);
	checkxorbit(xor, aOutNew, "REL_AUTOSOURCESELECT", REL_AUTOSOURCESELECT);
	checkxorbit(xor, aOutNew, "REL_OUT1SOURCESELECT", REL_OUT1SOURCESELECT);
	checkxorbit(xor, aOutNew, "REL_OUT2SOURCESELECT", REL_OUT2SOURCESELECT);
	checkxorbit(xor, aOutNew, "REL_OUTPUTENABLE", REL_OUTPUTENABLE);
	checkxorbit(xor, aOutNew, "REL_PWRSELF", REL_PWRSELF);
}

void emulationcallback(int aCallbacktype, ...) {
	va_list arglist;
	va_start(arglist, aCallbacktype);
	if (aCallbacktype == 0) {
		enum SwitchState oldstate, newstate;
		int oldout, newout;
		oldstate = va_arg(arglist, enum SwitchState);
		newstate = va_arg(arglist, enum SwitchState);
		oldout = va_arg(arglist, int);
		newout = va_arg(arglist, int);
		callbackStateSwitch(oldstate, newstate, oldout, newout);
	}
	va_end(arglist);
}

int main() {
	relaySwitchState(SWST_ISOAUTO_ON);
	fprintf(stderr, "--------------------------------------------------------------\n");
	relaySwitchState(SWST_AUTO_ON);
	return 0;
}
