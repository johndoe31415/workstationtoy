#ifndef __ERRORS_H__
#define __ERRORS_H__

enum resultCode {
	SUCCESS,
	ERR_EEPROM_VERSION_INVALID,
	ERR_EEPROM_HASH_INVALID,
	ERR_FLASH_HASH_INVALID,
	ERR_RELAIS_VOLTAGE_MISSING,
	ERR_RELAIS_VOLTAGE_MISSING_EMERGENCY,
	ERR_SLAVE_DEFECT_FRONTPANEL,
	ERR_SLAVE_DEFECT_CURRENTMONITOR,
	ERR_SLAVE_DEFECT_VOLTAGEMONITOR,
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
const char* getErrorString(enum resultCode aError);
const char* getErrorSymbolName(enum resultCode aError);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
