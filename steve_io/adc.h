/*
 * adc.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#ifndef ADC_H_
#define ADC_H_

void adc_init(char pin_mask, char refs);
int adc_read(char adc_pin);

#endif /* ADC_H_ */
