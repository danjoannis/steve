/*
 * ultrasonic.c
 *
 *  Created on: Nov 21, 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>
#include "util.h"
#include "pinout.h"
#include "ultrasonic.h"

void us_init()
{
	//Set Ultra Sonic Port as out
	US_DDR|=(1<<US_TRIG);
}

uint16_t us_measure()
{
	uint32_t i,result;

	//Send the trigger
	US_PORT|=(1<<US_TRIG);	//High
	_delay_us(15);
	US_PORT&=(~(1<<US_TRIG));//Low
	_delay_us(20);

	//Wait for the rising edge
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<US_ECHO))) continue; else break;
	}

	if(i==600000)
		return US_TIMEOUT;	//Indicates time out

	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<600000;i++)
	{
		if(US_PIN & (1<<US_ECHO))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
			break;
	}

	if(i==600000)
		return US_TIMEOUT;	//Indicates time out

	//Falling edge found

	result=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
		return US_NO_OBSTACLE;	//No obstacle
	else
		return (result>>1);
}
