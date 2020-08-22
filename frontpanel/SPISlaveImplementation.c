#include "SPISlave.h"
#include "Timer.h"
#include "LEDOutput.h"
#include "Keyboard.h"
#include "HAL.h"

void executeGetLEDPattern(struct fpCmd_GetLEDPattern *aCommand) {
	aCommand->slave.patternGreen = getLEDPattern((2 * aCommand->master.ledIndex) + 0);
	aCommand->slave.patternRed = getLEDPattern((2 * aCommand->master.ledIndex) + 1);
}

void executeSetLEDPattern(struct fpCmd_SetLEDPattern *aCommand) {
	setLEDPattern((2 * aCommand->master.ledIndex) + 0, aCommand->master.patternGreen);
	setLEDPattern((2 * aCommand->master.ledIndex) + 1, aCommand->master.patternRed);
}

void executeSetAllLEDPattern(struct fpCmd_SetAllLEDPattern *aCommand) {
	for (uint8_t i = 0; i < LEDCOUNT / 2; i++) {
		setLEDPattern((i * 2) + 0, aCommand->master.patternGreen);
		setLEDPattern((i * 2) + 1, aCommand->master.patternRed);
	}
}

void executeGetTiming(struct fpCmd_GetTiming *aCommand) {
	aCommand->slave.timerMaxValue = getTimerMaxValue();
}

void executeSetTiming(struct fpCmd_SetTiming *aCommand) {
	setTimerMaxValue(aCommand->master.timerMaxValue);
}

void executeReadKeyboard(struct fpCmd_ReadKeyboard *aCommand) {
	struct KeyboardQueueEntry keyboardRegister = getKeyboardRegister();
	aCommand->slave.keyboardEvent = keyboardRegister.event;
	aCommand->slave.pressedKey = keyboardRegister.pressedKey;
}

void executeMultiplexerTest(struct fpCmd_MultiplexerTest *aCommand) {
}


