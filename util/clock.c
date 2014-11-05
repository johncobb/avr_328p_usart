/*
 * clock.c
 *
 *  Created on: Oct 20, 2014
 *      Author: jcobb
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "clock.h"

volatile clock_time_t clock_millis;
//volatile clock_time_t future;

void clock_init()
{
	// timer ctc mode
	TCCR0A |= _BV(WGM01);

	// F_CPU/64/1000 = 125
	OCR0A = F_CPU/64/1000;
	// Enable timer set prescalar to 64
	TCCR0B |= _BV(CS01) | _BV(CS00);

	// Enable Output Compare Match A
	TIMSK0 = _BV(OCIE0A);
}

clock_time_t clock_time()
{
	return clock_millis;
}

void delay_millis(clock_time_t millis)
{
	clock_time_t future = clock_time() + millis;

	while(true)
	{
		if(clock_time() > future)
		{
			break;
		}
	}
}

ISR(TIMER0_COMPA_vect)
{
	clock_millis++;
}

void isr_tick()
{
	clock_millis++;
}



