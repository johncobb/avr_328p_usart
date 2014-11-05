/*
 * usart_driver.h
 *
 *  Created on: Nov 5, 2014
 *      Author: jcobb
 */

#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_


// usart parsing results
enum btle_parse_result {
 USART_TKNOTFOUND = 0,
 USART_TKFOUND,
 USART_TKERROR,
 USART_TKTIMEOUT
};

// token start and end
#define USART_TKSTART	'*'
#define USART_TKEND		'\r'


void usart_driver_init();
void usart_driver_tick();

#endif /* USART_DRIVER_H_ */
