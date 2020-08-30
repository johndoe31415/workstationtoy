#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>

#define delayMicroseconds(x)		delay_1_376_us((x) * 125UL / 172UL)

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void delay_millis(uint16_t milli_seconds);
void delay_1_376_us(uint16_t micro_seconds_1_376);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
