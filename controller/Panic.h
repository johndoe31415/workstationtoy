#ifndef __PANIC_H__
#define __PANIC_H__

#include "Errors.h"

#define panicMsg(msg, reason)		invokePanic(PSTR(msg), PSTR(__FILE__), __LINE__, (reason))
#define panic(reason)				invokePanic(NULL, PSTR(__FILE__), __LINE__, (reason))

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void invokePanic(const char *aMessage, const char *aFile, uint16_t aLine, enum resultCode aPanicReason);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
