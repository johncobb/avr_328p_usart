/*
 * main.c
 *
 *  Created on: Nov 5, 2014
 *      Author: jcobb
 */



#define F_CPU		800000

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "util/clock.h"
#include "util/config.h"
#include "usart/usart.h"
#include "usart/usart_driver.h"

// timeout helper
volatile clock_time_t future = 0;
bool timeout();
void set_timer(clock_time_t timeout);

int main()
{
	// led port
	DDRB |= _BV(PB5);

	clock_init();
	config_init();
	usart_driver_init();
	sei();
	usart_transmit_string("spike_328p_usart started...\r\n");
	usart_transmit_string("enter some text followed by a carriage return\r\n");
	while(true){

		usart_driver_tick();
		if(timeout()){
			// toggle led
			PORTB ^= _BV(PB5);
			set_timer(1000);
		}
	}

	return 0;
}


void set_timer(clock_time_t timeout)
{
	future = clock_time() + timeout;
}

// timeout routine to demonstrate clock_time
// being kept by pwm isr interrupt
bool timeout()
{
	bool timeout = false;

	if(clock_time() >= future)
	{
		set_timer(1000);
		timeout = true;

	}

	return timeout;
}
