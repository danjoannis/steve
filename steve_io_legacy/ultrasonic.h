/*
 * ultrasonic.h
 *
 *  Created on: Nov 21, 2015
 *      Author: Daniel
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define US_TIMEOUT 0xffff
#define	US_NO_OBSTACLE 0xfffe

void us_init();
uint16_t us_measure();

#endif /* ULTRASONIC_H_ */
