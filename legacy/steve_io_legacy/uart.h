/*
 * uart.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#ifndef UART_H_
#define UART_H_

#define USART0_BAUDRATE 38400
#define UBRR0_VALUE (((F_CPU / (USART0_BAUDRATE * 16UL))) - 1)
#define RX_BUFF 20

//UART0
void uart0_init(void);
void uart0_putChar(char ByteToSend);
void uart0_putString(char * StringToSend);
unsigned char uart0_getChar(void);
void uart0_getString(char * ReceivedString);

#endif /* UART_H_ */
