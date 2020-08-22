#ifndef __EEPROM_H__
#define __EEPROM_H__

#include <stdint.h>

struct eepromLayout {
	uint16_t layoutVersion;
	uint16_t flashPages;
	uint8_t flashMd5[16];
	uint8_t eepromMd5[16];
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
enum resultCode loadEEPROM(struct eepromLayout *aData);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
