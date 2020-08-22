#ifndef __MULTIPLEXER_H__
#define __MULTIPLEXER_H__

#include <stdint.h>

#define MULTIPLEXER_CNT			3

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void muxSetDirty(void);
void muxTest(const uint8_t *aInData, uint8_t *aOutData);
bool muxGetBit(uint16_t aBitNo);
void muxSetBit(uint16_t aBitNo, bool aValue);
void muxCommit(void);
void muxCommitOnChange(void);
void muxWriteRaw(const uint8_t *aData);
void muxInit(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
