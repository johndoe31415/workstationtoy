#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/eeprom.h>

#include "EEPROM.h"
#include "Errors.h"
#include "md5.h"

#define EXPECTED_EEPROM_LAYOUT			1

enum resultCode loadEEPROM(struct eepromLayout *aData) {
	/* Read EEPROM data block into RAM */
	eeprom_read_block(aData, 0, sizeof(struct eepromLayout));

	/* Check the EEPROM version */
	if (aData->layoutVersion != EXPECTED_EEPROM_LAYOUT) {
		return ERR_EEPROM_VERSION_INVALID;
	}

	/* Then check the EEPROM hash value itself */
	uint8_t hash[MD5_HASH_BYTES];
	md5_ctx_t md5Ctx;
	md5_init(&md5Ctx);
	md5_lastBlock(&md5Ctx, aData, (sizeof(struct eepromLayout) - sizeof(hash)) * 8);
	md5_ctx2hash((md5_hash_t*)hash, &md5Ctx);
	if (memcmp(hash, aData->eepromMd5, 16)) {
		return ERR_EEPROM_HASH_INVALID;
	}

	return SUCCESS;
}
