#ifndef __LEDOUTPUT_H__
#define __LEDOUTPUT_H__

#include <stdint.h>
#include <stdbool.h>

#define LEDCOUNT		20

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void setLEDPattern(uint8_t aLed, uint16_t aPattern);
uint16_t getLEDPattern(uint8_t aLed);
void ledTick(void);
void setAllLEDPattern(uint16_t aPattern);
void ledInit(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
