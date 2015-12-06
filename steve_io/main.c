/*
 * main.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motors.h"
#include "pinout.h"
#include "uart.h"
#include "adc.h"
#include "util.h"
#include "commands.h"
#include "ultrasonic.h"
#include "mpu9255.h"
#include "i2c.h"

int main(void)
{
	/* set pin 5 of PORTB for output*/
	//DDRB |= (1 << PB5);

	// Initialization functions
	uart0_init();
	us_init();
	adc_init(0, 0b00000011);
	motors_init();
	i2c_init();
	//Initalise_AccelGyro(ACCELRANGE_8g, GYRORANGE_2000DPS);

	// Serial welcome
	uart0_putString("Hello. My name is STEVE: Self Training Electronic Vehicle for Exploration.\r\n");
	uart0_putString("I am a robot. Right now I don't know very much, but I'm learning.\r\n");

	// Enable interrupts
	sei();

	while (1)
	{
		/* set pin 5 high to turn led on */
		//uart0_itoaWrite(25 + ((adc_read(8)-314) * 0.9));
		//uart0_putString("\r\n");
		//PORTB |= _BV(PORTB5);
		//_delay_ms(500);

		/* set pin 5 low to turn led off */
		//PORTB &= ~_BV(PORTB5);
		//_delay_ms(500);

		if (command_ready == TRUE)
		{
			copy_command();
			process_command();

			command_ready = FALSE;
			//uart0_putString("OK\r\n");
		}
	}
}

ISR (USART_RX_vect)
{
	// Get data from the USART in register
	data_in[data_count] = UDR0;

	// End of line!
	if (data_in[data_count] == '\r')
	{
		command_ready = TRUE;
		// Reset to 0, ready to go again
		data_count = 0;
	}
	else
	{
		data_count++;
	}
}
