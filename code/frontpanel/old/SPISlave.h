#ifndef __SPISLAVE_H__
#define __SPISLAVE_H__

/* Command format:
 *
 * W    W    R/W  R/W
 * CMD  PAR  VAL1 VAL2 
 *
 *																						Command	Response
 * CMD_GET_LED_PATTERN		W:[00-13]	R:LowPtrn	R:HighPtrn							2		2
 * CMD_SET_LED_PATTERN		W:[00-13]	W:LowPtrn	W:HighPtrn							4		0
 * CMD_SET_ALL_LED			W:LowPtrn	W:HighPtrn										1		0
 * CMD_GET_TIMING        	R:Timing													1		1
 * CMD_SET_TIMING        	W:Timing													2		0
 *
 * CMD_READ_KEYBOARD:		R:BtnStatus													1		1
 *
 * CMD_MUX_TEST:			W:Pattern	W:Pattern	W:Pattern	R:Ptrn	R:Ptrn	R:Ptrn	4		3
 * CMD_MUX_WRITE:			W:Pattern	W:Pattern	W:Pattern							4		0
 *
 */


enum commandByte {
	// LED commands
	CMD_GET_LED_PATTERN = 0,
	CMD_SET_LED_PATTERN = 1,
	CMD_SET_ALL_LED = 2,
	CMD_GET_TIMING = 3,
	CMD_SET_TIMING = 4,

	// Read keyboard queue command
	CMD_READ_KEYBOARD = 5,

	// Misc commands
	CMD_MUX_TEST = 6,
	CMD_MUX_WRITE = 7,
};

enum keyboardEventType {
	KBD_EVENT_NONE = 0,
	KBD_EVENT_PRESS_SHORT = 1,
	KBD_EVENT_PRESS_MEDIUM = 2,
	KBD_EVENT_PRESS_LONG = 3
};

enum keyboardEventKey {
	KBD_KEY_DEADMAN = 0,
	KBD_KEY_AUTO_TRANSFORMER = 1,
	KBD_KEY_ISOLATION_TRANSFORMER = 2,
	KBD_KEY_OUTPUT = 3
};

enum parameterByte {
	LED_OPERATION_GREEN = 0,
	LED_OPERATION_RED = 1,
	LED_ERROR_GREEN = 2,
	LED_ERROR_RED = 3,
	LED_AUTOMATIC_SHUTDOWN_GREEN = 4,
	LED_AUTOMATIC_SHUTDOWN_RED = 5,
	LED_TEMPERATURE_GREEN = 6,
	LED_TEMPERATURE_RED = 7,
	LED_PROTECTIVE_EARTH_GREEN = 8,
	LED_PROTECTIVE_EARTH_RED = 9,
	LED_PHASE_ERROR_GREEN = 10,
	LED_PHASE_ERROR_RED = 11,
	LED_OVERCURRENT_GREEN = 12,
	LED_OVERCURRENT_RED = 13,
	LED_AUTO_TRANSFORMER_GREEN = 14,
	LED_AUTO_TRANSFORMER_RED = 15,
	LED_ISOLATION_TRANSFORMER_GREEN = 16,
	LED_ISOLATION_TRANSFORMER_RED = 17,
	LED_OUTPUT_GREEN = 18,
	LED_OUTPUT_RED = 19,
};

#define LED_PAR_MIN			LED_OPERATION_GREEN
#define LED_PAR_MAX			LED_OUTPUT_RED

#ifdef SLAVE
/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void spiReset(void);
void spiSlaveInit(void);
/***************  AUTO GENERATED SECTION ENDS   ***************/
#endif

#endif
