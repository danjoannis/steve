/*
 * adc.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include "adc.h"

void adc_init(char pin_mask, char refs)
{
	DDRC &= ~pin_mask;
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS0) | (1 << ADEN));
	ADMUX |= (1 << ADLAR) | (refs << 6);
}

int adc_read(char adc_pin)
{
	ADMUX |= (adc_pin & 0x0F);

	int contents = 0;

	ADCSRA |= (1 << ADSC); //First ADC read

	while((ADCSRA >> ADSC) & 1);

	ADCSRA |= (1 << ADSC); //Second ADC read (for more accurate result)

	while((ADCSRA >> ADSC) & 1);

	contents |= (ADCL >> 6);
	contents |= (ADCH << 2);

	return contents; //Return second ADC read
}



