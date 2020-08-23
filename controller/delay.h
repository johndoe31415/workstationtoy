#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>

#define delayMicroseconds(x)		delayMicroseconds1376((x) * 125UL / 172UL)

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void delayMillis(uint16_t aMillis);
void delayMicroseconds1376(uint16_t aMicros);
void delayNop(uint16_t aRepetitions);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
