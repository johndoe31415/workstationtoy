#ifndef __SPISLAVEFP_H__
#define __SPISLAVEFP_H__

#include <stdint.h>
#include <stdbool.h>

#ifndef PACKED
#define PACKED				__attribute__ ((packed))
#endif

#ifndef static_assert
#define static_assert(x)	_Static_assert(x, #x)
#endif

#if defined(SPI_MASTER)
#define MODIFIER_MASTER
#define MODIFIER_SLAVE			const
#elif defined(SPI_SLAVE)
#define MODIFIER_MASTER			const
#define MODIFIER_SLAVE
#else
#error Neither SPI_MASTER nor SPI_SLAVE is defined.
#endif

enum fpEnum_ledIndex {
	LED_OPERATION,
	LED_ERROR,
	LED_AUTOMATIC_SHUTDOWN,
	LED_TEMPERATURE,
	LED_PROTECTIVE_EARTH,
	LED_PHASE_ERROR,
	LED_OVERCURRENT,
	LED_AUTO_TRANSFORMER,
	LED_ISOLATION_TRANSFORMER,
	LED_OUTPUT,
};

enum fpEnum_keyboardEvent {
	KBD_EVENT_NONE,
	KBD_EVENT_PRESS_SHORT,
	KBD_EVENT_PRESS_MEDIUM,
	KBD_EVENT_PRESS_LONG,
};

enum fpEnum_keyboardKey {
	KBD_KEY_DEAD_MAN = 0x0,
	KBD_KEY_AUTO_TRANSFORMER = 0x1,
	KBD_KEY_ISOLATION_TRANSFORMER = 0x2,
	KBD_KEY_OUTPUT = 0x3,
	KBD_KEY_NONE,
};

#define FP_GETLEDPATTERN_CMDID			0x0
#define FP_GETLEDPATTERN_MASTERLEN		4
#define FP_GETLEDPATTERN_DELAY_US		500
#define FP_GETLEDPATTERN_TOTALLEN		10
struct fpCmd_GetLEDPattern {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		enum fpEnum_ledIndex ledIndex;
	} master;
	MODIFIER_SLAVE struct {
		uint16_t patternRed;
		uint16_t patternGreen;
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_GetLEDPattern) == 10);
/*****************************************************************************
	struct fpCmd_GetLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_GETLEDPATTERN_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_GETLEDPATTERN_TOTALLEN, FP_GETLEDPATTERN_MASTERLEN, FP_GETLEDPATTERN_DELAY_US);
*****************************************************************************/


#define FP_SETLEDPATTERN_CMDID			0x1
#define FP_SETLEDPATTERN_MASTERLEN		8
#define FP_SETLEDPATTERN_DELAY_US		500
#define FP_SETLEDPATTERN_TOTALLEN		10
struct fpCmd_SetLEDPattern {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		enum fpEnum_ledIndex ledIndex;
		uint16_t patternRed;
		uint16_t patternGreen;
	} master;
	MODIFIER_SLAVE struct {
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_SetLEDPattern) == 10);
/*****************************************************************************
	struct fpCmd_SetLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_SETLEDPATTERN_TOTALLEN, FP_SETLEDPATTERN_MASTERLEN, FP_SETLEDPATTERN_DELAY_US);
*****************************************************************************/


#define FP_SETALLLEDPATTERN_CMDID			0x2
#define FP_SETALLLEDPATTERN_MASTERLEN		7
#define FP_SETALLLEDPATTERN_DELAY_US		500
#define FP_SETALLLEDPATTERN_TOTALLEN		9
struct fpCmd_SetAllLEDPattern {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		uint16_t patternRed;
		uint16_t patternGreen;
	} master;
	MODIFIER_SLAVE struct {
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_SetAllLEDPattern) == 9);
/*****************************************************************************
	struct fpCmd_SetAllLEDPattern cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETALLLEDPATTERN_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_SETALLLEDPATTERN_TOTALLEN, FP_SETALLLEDPATTERN_MASTERLEN, FP_SETALLLEDPATTERN_DELAY_US);
*****************************************************************************/


#define FP_GETTIMING_CMDID			0x3
#define FP_GETTIMING_MASTERLEN		3
#define FP_GETTIMING_DELAY_US		500
#define FP_GETTIMING_TOTALLEN		6
struct fpCmd_GetTiming {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
	} master;
	MODIFIER_SLAVE struct {
		uint8_t timerMaxValue;
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_GetTiming) == 6);
/*****************************************************************************
	struct fpCmd_GetTiming cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_GETTIMING_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_GETTIMING_TOTALLEN, FP_GETTIMING_MASTERLEN, FP_GETTIMING_DELAY_US);
*****************************************************************************/


#define FP_SETTIMING_CMDID			0x4
#define FP_SETTIMING_MASTERLEN		4
#define FP_SETTIMING_DELAY_US		500
#define FP_SETTIMING_TOTALLEN		6
struct fpCmd_SetTiming {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		uint8_t timerMaxValue;
	} master;
	MODIFIER_SLAVE struct {
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_SetTiming) == 6);
/*****************************************************************************
	struct fpCmd_SetTiming cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_SETTIMING_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_SETTIMING_TOTALLEN, FP_SETTIMING_MASTERLEN, FP_SETTIMING_DELAY_US);
*****************************************************************************/


#define FP_READKEYBOARD_CMDID			0x5
#define FP_READKEYBOARD_MASTERLEN		3
#define FP_READKEYBOARD_DELAY_US		500
#define FP_READKEYBOARD_TOTALLEN		7
struct fpCmd_ReadKeyboard {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
	} master;
	MODIFIER_SLAVE struct {
		enum fpEnum_keyboardEvent keyboardEvent;
		enum fpEnum_keyboardKey pressedKey;
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_ReadKeyboard) == 7);
/*****************************************************************************
	struct fpCmd_ReadKeyboard cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_READKEYBOARD_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_READKEYBOARD_TOTALLEN, FP_READKEYBOARD_MASTERLEN, FP_READKEYBOARD_DELAY_US);
*****************************************************************************/


#define FP_MULTIPLEXERTEST_CMDID			0x6
#define FP_MULTIPLEXERTEST_MASTERLEN		6
#define FP_MULTIPLEXERTEST_DELAY_US		500
#define FP_MULTIPLEXERTEST_TOTALLEN		11
struct fpCmd_MultiplexerTest {
	MODIFIER_MASTER struct {
		uint8_t cmdId;
		uint16_t crc;
		uint8_t writePattern[3];
	} master;
	MODIFIER_SLAVE struct {
		uint8_t readPattern[3];
		uint16_t crc;
	} slave;
} PACKED;
static_assert(sizeof(struct fpCmd_MultiplexerTest) == 11);
/*****************************************************************************
	struct fpCmd_MultiplexerTest cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.master.cmdId = FP_MULTIPLEXERTEST_CMDID;
	spiTransmitToSlave(SLAVE_FRONTPANEL, &cmd, FP_MULTIPLEXERTEST_TOTALLEN, FP_MULTIPLEXERTEST_MASTERLEN, FP_MULTIPLEXERTEST_DELAY_US);
*****************************************************************************/



#ifdef SPI_SLAVE
void spiSlaveInit(void);
void checkSPIForReset(void);

void executeGetLEDPattern(struct fpCmd_GetLEDPattern *aCommand);
void executeSetLEDPattern(struct fpCmd_SetLEDPattern *aCommand);
void executeSetAllLEDPattern(struct fpCmd_SetAllLEDPattern *aCommand);
void executeGetTiming(struct fpCmd_GetTiming *aCommand);
void executeSetTiming(struct fpCmd_SetTiming *aCommand);
void executeReadKeyboard(struct fpCmd_ReadKeyboard *aCommand);
void executeMultiplexerTest(struct fpCmd_MultiplexerTest *aCommand);
#endif

#endif
