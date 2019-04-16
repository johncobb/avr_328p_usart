/*
 * usart_driver.c
 *
 *  Created on: Nov 5, 2014
 *      Author: jcobb
 */

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "../util/defines.h"
#include "usart.h"
#include "usart_driver.h"

#define USART_MAX_CHARS		128

char HEX_DIGITS[] = "0123456789abcdef";

char usart_lines[USART_MAX_CHARS+1];
char usart_line_buffer[USART_MAX_CHARS+1];
int usart_line_index = 0;

void init_buffer();
void init_lines();
bool handle_data();
uint8_t parse_data(char *token, char **out);

void usart_driver_init()
{
	usart_init();
	init_buffer();
	init_lines();
}

void usart_driver_tick()
{
	if(usart_data_available()) {
		if(handle_data()) {
			// echo back input
			usart_transmit_string(usart_lines);
			usart_transmit_string("\r\n");
			// reset usart_lines
			init_lines();

		}
	}
}

void init_buffer()
{
	usart_line_index = 0;
	memset(usart_line_buffer, '\0', sizeof(usart_line_buffer));
}

void init_lines()
{
	memset(usart_lines, '\0', sizeof(usart_lines));
}

// check to see if we have a new line
bool handle_data()
{

	char c = usart_data_read();

	// ignore null terminated strings
	if(c == '\0') return false;
	// prevent buffer overrun
	if(usart_line_index >= USART_MAX_CHARS) return false;

	// store character in usart_line_buffer
	usart_line_buffer[usart_line_index] = c;
	usart_line_index++;

	// check for end of line
	if(c == USART_TKEND) {
		// copy new message into buffer
		strcpy(usart_lines, usart_line_buffer);
		init_buffer();
		return true;
	}

	return false;
}

uint8_t parse_data(char *token, char **out)
{
	uint8_t *ptr = NULL;
	// TODO: review warning
	if((ptr == strstr(usart_lines, token)))
	{
		if(out != NULL) *out = ptr;
		return USART_TKFOUND;
	}
	else
		return USART_TKNOTFOUND;
}
