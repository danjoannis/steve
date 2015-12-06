/*
 * uart.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include "uart.h"

//UART0

void uart0_init(){
	/* Set baud rate */
	UBRR0 = UBRR0_VALUE; // thank you AVR-GCC
	/* Do not double transmission speed */
	UCSR0A &= ~(1<<U2X0);
	/* Enable receiver and transmitter and interrupt */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8 data bits */
	UCSR0C |= (1 <<UCSZ00)| (1 << UCSZ01);
}

void uart0_putChar(char send){
    while ( !(UCSR0A & (1 << UDRE0)) ) {}; 	// Wait until ready for transmission
    UDR0 = send; 							// Transmit char / 8-bit data
} 

unsigned char uart0_getChar(void){
    if(UCSR0A & (1 << RXC0)){
	    return UDR0;
	}
	else return 0;
}

void uart0_putString(char * send){
	while(*send){
		uart0_putChar(*send++);
	}
}

void uart0_getString(char * ReceivedString){
	int i = 0;

	while(UCSR0A & (1 << RXC0)){
		ReceivedString[i] = UDR0;
		i++;
		if(i > RX_BUFF) break;
	}
}
