/*
 * pinout.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#ifndef PINOUT_H_
#define PINOUT_H_

// Motor controller
#define MOTOR_DDR DDRD
#define MOTOR_PORT PORTD
#define MOTOR_EN1 0
#define MOTOR_EN2 1
#define MOTOR_A1 2
#define MOTOR_B1 3
#define MOTOR_A2 4
#define MOTOR_B2 5

// Ultrasonic rangefinder
#define US_DDR DDRD
#define US_PORT PORTD
#define US_PIN PIND
#define US_TRIG 6
#define US_ECHO 7

#endif /* PINOUT_H_ */
