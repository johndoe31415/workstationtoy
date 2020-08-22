#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "md5.h"
#include "Debug.h"
#include "Errors.h"
#include "Panic.h"
#include "EEPROM.h"

static void genFlashSignature(uint16_t aPageCount, uint8_t *aDigest) {
	uint8_t shadowPage[SPM_PAGESIZE];
	md5_ctx_t md5ctx;
	md5_init(&md5ctx);
	memset(shadowPage, 0, sizeof(shadowPage));
	for (uint16_t i = 0; i < aPageCount; i++) {
		uint32_t offset = (uint32_t)i * SPM_PAGESIZE;
		memcpy_PF(shadowPage, (uint_farptr_t)offset, SPM_PAGESIZE);
		for (uint8_t j = 0; j < SPM_PAGESIZE / MD5_BLOCK_BYTES; j++) {
			md5_nextBlock(&md5ctx, shadowPage + (MD5_BLOCK_BYTES * j));
		}
	}
	md5_lastBlock(&md5ctx, NULL, 0);
	md5_ctx2hash((md5_hash_t*)aDigest, &md5ctx);
}

static enum resultCode checkFlashIntegrity(void) {
	enum resultCode result;

	struct eepromLayout eepromData;
	result = loadEEPROM(&eepromData);
	if (result != SUCCESS) {
		return result;
	}
	
	uint8_t hash[16];
	genFlashSignature(eepromData.flashPages, hash);
	
	if (memcmp(eepromData.flashMd5, hash, 16)) {
		/* Flash signature invalid */
		return ERR_FLASH_HASH_INVALID;
	}

	return SUCCESS;
}

void flashIntegrityCheck(void) {
	enum resultCode result = checkFlashIntegrity();
	if (result != SUCCESS) {
		panicMsg("Flash integrity check failed", result);
	}
}
