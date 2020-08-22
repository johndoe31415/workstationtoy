#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "RS232.h"
#include "HAL.h"
#include "Debug.h"

#include "../frontpanel/SPISlave.h"
#include "SPI.h"
#include "Buzzer.h"
#include "Frontpanel.h"

static int rs232PutChar(char aChar, FILE *aStream);

uint16_t crctest(const uint8_t *a, uint8_t b);

ISR(USART1_RX_vect) {
	volatile uint8_t data = UDR1;
	(void)data;
	switch (data) {
		
		case 'a':
			mprintf("GetFPKey:\r\n");
			getFrontpanelKey();
			break;
		
		case 'w':
			ledTest();
			break;
		
		
	};
#if 0
	if (data == 'q') {
		struct fpCmd_SetLEDPattern cmd;
		cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
		cmd.master.ledIndex = LED_OPERATION;
		cmd.master.patternRed = 0xffff;
		cmd.master.patternGreen = 0;
		selectSPISource(FRONTPANEL_NORMAL);		
		spiTransmit(&cmd, sizeof(cmd));
		deselectSPI();
	} else if (data == 'w') {
		struct fpCmd_SetLEDPattern cmd;
		cmd.master.cmdId = FP_SETLEDPATTERN_CMDID;
		cmd.master.ledIndex = LED_OPERATION;
		cmd.master.patternRed = 0;
		cmd.master.patternGreen = 0xffff;
		selectSPISource(FRONTPANEL_NORMAL);		
		spiTransmit(&cmd, sizeof(cmd));
		deselectSPI();
	} else if (data == 'a') {
		struct fpCmd_GetLEDPattern cmd;
		memset(&cmd, 0, sizeof(cmd));
		cmd.master.cmdId = FP_GETLEDPATTERN_CMDID;
		cmd.master.ledIndex = LED_ERROR;
		selectSPISource(FRONTPANEL_NORMAL);		
		spiTransmitWithPause(&cmd, sizeof(cmd), FP_GETLEDPATTERN_MASTERLEN, FP_GETLEDPATTERN_DELAY_US);		
		deselectSPI();
		mprintf("Result: red=%x green=%x\r\n", cmd.slave.patternRed, cmd.slave.patternGreen);
	}
#endif
}

static void initRs232Stdout(void) {
	static FILE uartStdout = FDEV_SETUP_STREAM(rs232PutChar, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartStdout;
}

static int rs232PutChar(char aChar, FILE *aStream) {
	rs232TransmitChar(aChar);
	return 1;
}

void rs232TransmitChar(unsigned char aChar) {
	while (!(UCSR1A & _BV(UDRE1)));		/* Wait until data register empty */
	UDR1 = aChar;
}

void initRs232(void) {
	UBRR1 = 8;												/* 115200 Baud @ 16 MHz */
	UCSR1B = _BV(RXCIE1) | _BV(TXEN1) | _BV(RXEN1);			/* Enable transmitter and receiver, RXC IRQ */
	initRs232Stdout();
}

