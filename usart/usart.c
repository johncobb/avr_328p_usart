/*
 * usart_btle.c
 *
 *  Created on: Oct 20, 2014
 *      Author: jcobb
 */

//#define BAUD 9600
#define BAUD 38400
//#define BAUD 57600
//#define BAUD 115200
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "../util/clock.h"
#include "usart.h"

#include <util/setbaud.h>
USART_BUFFER usart_buffer = {{0},0,0};

const unsigned char BTLE_hex[] PROGMEM = "0123456789ABCDEF";

usart_rx_cb_t usart_rx_cb;

static void _usart_set_rx_cb(usart_rx_cb_t cb);

static void _usart_set_rx_cb(usart_rx_cb_t cb)
{
	usart_rx_cb = cb;
}

void usart_init()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// Enble receiver and transmitter
	UCSR0B |= (1<<RXCIE0) | (1<<TXEN0);

	// Set rx and tx enable bits
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	// Set databits to 8
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// not in use at this time
void usart_init_cb(usart_rx_cb_t cb)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// Enble receiver and transmitter
	UCSR0B |= (1<<RXCIE0) | (1<<TXEN0);

	// Set rx and tx enable bits
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	// Set databits to 8
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

	_usart_set_rx_cb(cb);
}

void usart_put_char(unsigned char c)
{
	int i = (unsigned int)(usart_buffer.head + 1) % USART_RX_BUFFER_SIZE;

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if (i != usart_buffer.tail) {
		usart_buffer.buffer[usart_buffer.head] = c;
		usart_buffer.head = i;
	}
}


void usart_clear_buffer()
{
	memset(&usart_buffer, 0, sizeof(USART_BUFFER));
}

uint8_t usart_data_available()
{
	return (uint8_t)(USART_RX_BUFFER_SIZE + usart_buffer.head - usart_buffer.tail) % USART_RX_BUFFER_SIZE;
}

uint8_t usart_data_read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (usart_buffer.head == usart_buffer.tail) {
		return -1;
	} else {
		uint8_t c = usart_buffer.buffer[usart_buffer.tail];
		usart_buffer.tail = (unsigned int)(usart_buffer.tail + 1) % USART_RX_BUFFER_SIZE;
		return c;
	}
}

void usart_transmit(uint8_t data )
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void usart_transmit_bytes(char data[], int size)
{
	for (int i=0;i<size;i++)
	{
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = data[i];
	}
}

void usart_transmit_string(char * data)
{
	unsigned char c = *data;

	while (c) {
		while (!( UCSR0A & (1<<UDRE0)));
		UDR0 = c;
		c = *(++data);
	}
}

ISR(USART_RX_vect)
{
	char data = UDR0;

	usart_put_char(data);
}
