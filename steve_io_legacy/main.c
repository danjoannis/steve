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
	// Initialization functions
	uart0_init();
	us_init();
	adc_init(0, 0b00000011);
	motors_init();
	i2c_init();
	//Initalise_AccelGyro(ACCELRANGE_8g, GYRORANGE_2000DPS);

	// Serial welcome
	uart0_putString("Hello. My name is STEVE.\r\n");

	// Enable interrupts
	sei();

	while (1)
	{
		if (command_ready == TRUE)
		{
			copy_command();
			process_command();

			command_ready = FALSE;
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
