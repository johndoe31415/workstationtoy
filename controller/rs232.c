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

static int rs232_putchar(char aChar, FILE *aStream);

uint16_t crc_test(const uint8_t *a, uint8_t b);

ISR(USART1_RX_vect) {
	volatile uint8_t data = UDR1;
	(void)data;
	rs232_tx_char(data+1);
	switch (data) {

		case 'a':
			fp_get_button_event();
			break;

		case 'w':
			fp_test_leds();
			break;
	};
}

static void rs232_init_stdout(void) {
	static FILE uartStdout = FDEV_SETUP_STREAM(rs232_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartStdout;
}

static int rs232_putchar(char aChar, FILE *aStream) {
	rs232_tx_char(aChar);
	return 1;
}

void rs232_tx_char(unsigned char aChar) {
	while (!(UCSR1A & _BV(UDRE1)));		/* Wait until data register empty */
	UDR1 = aChar;
}

void init_rs232(void) {
	UBRR1 = 8;												/* 115200 Baud @ 16 MHz */
	UCSR1B = _BV(RXCIE1) | _BV(TXEN1) | _BV(RXEN1);			/* Enable transmitter and receiver, RXC IRQ */
	rs232_init_stdout();
}

