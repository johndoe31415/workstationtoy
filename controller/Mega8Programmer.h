#ifndef __MEGA8PROGRAMMER_H__
#define __MEGA8PROGRAMMER_H__

#define ATMEGA8_PAGESIZE			64
#define ATMEGA8_IDENTIFIER			0x1e9307UL
//#define ATMEGA8_FUSECONFIG			0xd9ceUL
#define ATMEGA8_FUSECONFIG			0xd1ceUL		/* momentaner TODO workaround weil fuse schreiben nicht geht?? */

#define ATMEGA88_PAGESIZE			64
#define ATMEGA88_IDENTIFIER			0x1e930aUL
#define ATMEGA88_FUSECONFIG			0xf9dff6UL		/* Fast crystal */
//#define ATMEGA88_FUSECONFIG			0xf9df62UL			/* Default config */

enum detectedChip {
	CHIP_NONE = 0,
	CHIP_ATMEGA8,
	CHIP_ATMEGA88
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void initSlaveDevices(void);
void pgmDebug(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
