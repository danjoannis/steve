/*
 * commands.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#define CHAR_NEWLINE '\n'
#define CHAR_RETURN '\r'
#define RETURN_NEWLINE "\r\n"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <string.h>
#include "commands.h"
#include "uart.h"
#include "util.h"
#include "motors.h"
#include "mpu9255.h"

void copy_command()
{
	// The USART might interrupt this - don't let that happen!
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		// Copy the contents of data_in into command_in
		memcpy(command_in, data_in, 8);

		// Now clear data_in, the USART can reuse it now
		memset(data_in[0], 0, 8);
	}
}

/*
 * Command Legend (ASCII)
 *
 * 		Format: _OP_ ...
 * 		Ex:		A=B3
 *
 * D - Drive
 * 			F - Forward
 * 			R - Reverse
 * 				# - Duty (binary)
 * 					# - Distance (binary)
 * 		Ex: D=F(0b00001010)(0b00010100)
 *
 * T - Turn
 * 			L - Left
 * 			R - Right
 *
 */

void process_command()
{
	switch (command_in[0])
	{
	case 'D':								// Drive command
		if (command_in[1] == '?')
		{
			// Do the query action for D
			uart0_putString("Drive\r\n");
		}
		else if (command_in[1] == '=')
		{
			//uart0_putString("GO!\r\n");
			motors_go_tank(command_in[2], command_in[3], command_in[4], command_in[5]);
			//motors_drive_tank(command_in[2] - 0x30, 50, 5);
		}
		else if (command_in[1] == 'B')
		{
			_delay_ms(4000);
			motors_go_tank(TRUE,TRUE,100,100);
		}
		break;
	case 'Q':								// Query command
		if (command_in[1] == '?')
		{
			if (command_in[2] == 'U')
			{
				uint16_t result = us_measure();
				uart0_itoaWrite(result/58);
				uart0_putString("\r\n");
			}
			else if (command_in[2] == 'M')
			{
				uart0_putString("Trig Compass");
				Trigger_Compass();
				uart0_putString("Read Compass");
				uart0_itoaWrite(Read_Compass(COMP_XOUT_L));
				uart0_putString("Done");
			}
		}
		break;
	case 'A':
		if (command_in[1] == '?')
		{
			// Do the query action for R
			uart0_putString("Name .:. A=\r\n");
		}
		else if (command_in[1] == '=')
		{
			// Do the set action for A
		}
		break;
	default:
		uart0_putString("CMD Error\r\n");
		break;
	}
}

