#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "rs232.h"
#include "hal.h"

#include "../frontpanel/SPISlave.h"
#include "spi.h"
#include "buzzer.h"
#include "frontpanel.h"

static int rs232PutChar(char aChar, FILE *aStream);

uint16_t crc_test(const uint8_t *a, uint8_t b);

ISR(USART1_RX_vect) {
	volatile uint8_t data = UDR1;
	(void)data;
	switch (data) {

		case 'a':
			getFrontpanelKey();
			break;

		case 'w':
			ledTest();
			break;
	};
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

