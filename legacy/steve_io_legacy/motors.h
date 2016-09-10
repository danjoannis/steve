/*
 * motors.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#ifndef MOTORS_H_
#define MOTORS_H_

// Direction
#define NEUTRAL 0
#define FORWARD 1
#define REVERSE 2
#define BRAKE	3
// Heading
#define CENTRE 	0
#define LEFT 	1
#define RIGHT 	2

void motors_init();
// Tank body
void motors_drive_tank(char direction, char duty, double distance);
void motors_go_tank(char direction, char heading, char duty, double distance);
void motors_turn_tank(char heading, char duty, double distance);
// Car body
void motors_drive_car(char direction, char duty, double distance);
void motors_go_car(char direction, char heading, char duty, double distance);
void motors_turn_car(char heading, char duty, double distance);

#endif /* MOTORS_H_ */
