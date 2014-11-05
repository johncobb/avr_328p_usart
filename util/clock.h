/*
 * clock.h
 *
 *  Created on: Oct 20, 2014
 *      Author: jcobb
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdlib.h>
#include <stdint.h>

typedef uint32_t clock_time_t;

extern volatile clock_time_t clock_millis;

void clock_init();
clock_time_t clock_time();
void delay_millis(clock_time_t millis);
void isr_tick();

#endif /* CLOCK_H_ */
