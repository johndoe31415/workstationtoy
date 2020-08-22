#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <stdbool.h>

#include <avr/pgmspace.h>

#include "TimeKeeper.h"

#define mprintf(msg, ...)

#define softassert(cond)

#define logmsg(msg, ...)			logmsg_P(PSTR(msg), ## __VA_ARGS__)

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void logmsg_P(const char *aMessage, ...);
void softassertionFail(const char *aMessage, const char *aFile, uint16_t aLine);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
