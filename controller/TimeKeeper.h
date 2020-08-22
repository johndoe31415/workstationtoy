#ifndef __TIMEKEEPER_H__
#define __TIMEKEEPER_H__

#include <stdint.h>

typedef char timekeeperStrbuf[12];

struct time {
	uint32_t seconds;
	uint8_t fraction;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void getTime(struct time *aTime);
uint32_t getTimeSeconds(void);
void timeDiff(struct time *aTime);
void formatTime(const struct time *aTime, timekeeperStrbuf aBuffer);
void disableTimekeeper(void);
void initTimekeeper(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
