#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "RS232.h"
#include "HAL.h"

ISR(USART_RX_vect) {
	volatile uint8_t data = UDR0;
	(void)data;
	if (data == ' ') {
		rs232TransmitCRLF();
	}
}

void rs232TransmitChar(unsigned char aChar) {
	while (!(UCSR0A & _BV(UDRE0)));		/* Wait until data register empty */
	UDR0 = aChar;
}

static void rs232TransmitNibble(uint8_t aNibble) {
	if (aNibble < 10) {
		rs232TransmitChar('0' + aNibble);
	} else {
		rs232TransmitChar('a' + aNibble - 10);
	}
}

void rs232TransmitHex(uint16_t aNumber) {
	rs232TransmitChar('0');
	rs232TransmitChar('x');
	rs232TransmitNibble((aNumber & 0xf000) >> 12);
	rs232TransmitNibble((aNumber & 0x0f00) >> 8);
	rs232TransmitNibble((aNumber & 0x00f0) >> 4);
	rs232TransmitNibble((aNumber & 0x000f) >> 0);
}

void rs232Dbg(char aIdentifier, uint16_t aNumber) {
	rs232TransmitChar(aIdentifier);
	rs232TransmitChar(' ');
	rs232TransmitHex(aNumber);
	rs232TransmitCRLF();
}

void rs232TransmitCRLF(void) {
	rs232TransmitChar('\r');
	rs232TransmitChar('\n');
}

void initRs232(void) {
	UBRR0 = 8;												/* 115200 Baud @ 16 MHz */
	UCSR0B = _BV(RXCIE0) | _BV(TXEN0) | _BV(RXEN0);			/* Enable transmitter and receiver, RXC IRQ */
}

