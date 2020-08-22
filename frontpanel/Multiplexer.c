#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "HAL.h"
#include "Multiplexer.h"

static uint8_t muxValues[MULTIPLEXER_CNT];
static bool dirty;

void muxSetDirty(void) {
	dirty = true;
}

static void muxWriteBit(bool aBit) {
	Mux_DS_SetConditional(aBit);
	Mux_SHCP_PulseNop();
}

static bool muxReadBit(void) {
	bool value = Mux_Q7S_IsActive();
	Mux_SHCP_PulseNop();
	return value;
}

static void muxWrite(const uint8_t *aData) {
	for (uint8_t i = 0; i < MULTIPLEXER_CNT; i++) {
		for (int8_t j = 7; j >= 0; j--) {
			muxWriteBit((aData[i] & (1 << j)) != 0);
		}
	}
}

static void muxRead(uint8_t *aData) {
	for (uint8_t i = 0; i < MULTIPLEXER_CNT; i++) {
		aData[i] = 0;
		for (int8_t j = 7; j >= 0; j--) {
			aData[i] |= muxReadBit() ? (1 << j) : 0;
		}
	}
}

void muxTest(const uint8_t *aInData, uint8_t *aOutData) {
	muxWrite(aInData);
	muxRead(aOutData);
}

bool muxGetBit(uint16_t aBitNo) {
	return (muxValues[aBitNo / 8] & (1 << (aBitNo % 8))) != 0;
}

void muxSetBit(uint16_t aBitNo, bool aValue) {
	if (muxGetBit(aBitNo) != aValue) {
		dirty = true;
	}
	if (aValue) {
		muxValues[aBitNo / 8] |= (1 << (aBitNo % 8));
	} else {
		muxValues[aBitNo / 8] &= ~(1 << (aBitNo % 8));
	}
}

void muxCommit(void) {
	dirty = false;
	muxWrite(muxValues);
	Mux_STCP_PulseNop();
}

void muxCommitOnChange(void) {
	if (dirty) {
		muxCommit();
	}
}

void muxWriteRaw(const uint8_t *aData) {
	muxWrite(aData);
	Mux_STCP_PulseNop();
}

void muxInit(void) {
	memset(muxValues, 0, MULTIPLEXER_CNT);
	muxCommit();
	Mux_OE_SetActive();
}

