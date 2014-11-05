/*
 * log.h
 *
 *  Created on: Oct 20, 2014
 *      Author: jcobb
 */

#ifndef USART_BTLE_H_
#define USART_BTLE_H_

typedef void (*usart_rx_cb_t)(uint8_t);
typedef void (*usart_out_cb_t)(uint8_t);

#define USART_RX_BUFFER_SIZE 512

typedef struct
{
	unsigned char buffer[USART_RX_BUFFER_SIZE];
	int head;
	int tail;
} USART_BUFFER;

extern USART_BUFFER usart_buffer;
void usart_tick();
void usart_init();
void usart_init_cb(usart_out_cb_t cb);
void usart_put_char(unsigned char c);
void usart_clear_buffer();
uint8_t usart_data_available(void);
uint8_t usart_data_read(void);
void usart_transmit(uint8_t data );
void usart_transmit_bytes(char data[], int size);
void usart_transmit_string(char * data);

#endif /* USART_BTLE_H_ */
