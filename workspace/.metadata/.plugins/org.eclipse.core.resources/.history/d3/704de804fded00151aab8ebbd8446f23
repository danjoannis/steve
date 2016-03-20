/*
 * motors.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>

#include "motors.h"
#include "wiring.h"

#include "util.h"
#include "pinout.h"

void motors_init()
{
	// Configure outputs
	MOTOR_DDR |= (1 << MOTOR_EN1) | (1 << MOTOR_EN2) | (1 << MOTOR_A1)
			| (1 << MOTOR_B1) | (1 << MOTOR_A2) | (1 << MOTOR_B2);

	// Set outputs low
	MOTOR_PORT &= ~((1 << MOTOR_EN1) | (1 << MOTOR_EN2) | (1 << MOTOR_A1)
			| (1 << MOTOR_B1) | (1 << MOTOR_A2) | (1 << MOTOR_B2));
}

// Tank body

void motors_drive_tank(char direction, char duty, double distance)
{
	// Todo: Not be lazy and actually implement PWM

	//Forward: MOTOR_A = HIGH, MOTOR_B = LOW
	//Reverse: MOTOR_A = LOW, MOTOR_B = HIGH
	//Brake: MOTOR_A = MOTOR_B

	double delay_on = ((double)duty / 100) * 500;			// Sets the on-time for the motor
	double delay_off = (500 - delay_on);					// Sets the off-time for the motor

	char output = (1 << MOTOR_A1) | (1 << MOTOR_EN1) | (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Default forward

	if (direction == REVERSE)
	{
		output = (1 << MOTOR_B1) | (1 << MOTOR_EN1) | (1 << MOTOR_B2) | (1 << MOTOR_EN2);		// Reverse override
	}

	while (distance > 0)
	{
		MOTOR_PORT |= output;
		_delay_us(delay_on);
		MOTOR_PORT &= ~output;
		_delay_us(delay_off);
		distance -= 0.025;									// Arbitrary decrement
	}

	analogWrite(MOTOR_PORT, 255);
}

void motors_go_tank(char direction, char heading, char duty, double distance)
{
	double drive_delay_on = ((double) duty / 100) * 500;			// Sets the on-time for the motor
	double drive_delay_off = (500 - drive_delay_on);				// Sets the off-time for the motor

	char drive_output;
	char steering_output;

	if (heading == LEFT)
	{
	steering_output  = (1 << MOTOR_B1) | (1 << MOTOR_EN1) | (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Motor to slow to turn, default left
	}
	else if (heading == RIGHT)
	{
		steering_output = (1 << MOTOR_A1) | (1 << MOTOR_EN1) | (1 << MOTOR_B2) | (1 << MOTOR_EN2);		// Right override
	}
	else if (heading == CENTRE)
	{
		steering_output = 0;														// Centre override
	}

	if (direction == FORWARD)
	{
		drive_output = (1 << MOTOR_A1) | (1 << MOTOR_EN1) | (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Default forward
	}
	else if (direction == REVERSE)
	{
		drive_output = (1 << MOTOR_B1) | (1 << MOTOR_EN1) | (1 << MOTOR_B2) | (1 << MOTOR_EN2);			// Reverse override
	}
	else if (direction == NEUTRAL)
	{
		drive_output = 0;
	}
	else if (direction == BRAKE)
	{
		drive_output = (1 << MOTOR_A1) | (1 << MOTOR_B1) | (1 << MOTOR_EN1) | (1 << MOTOR_A2) | (1 << MOTOR_B2) | (1 << MOTOR_EN2);
	}

	//drive_output |= steering_output;

	while (distance > 0)
	{
		MOTOR_PORT |= drive_output;
		_delay_us(drive_delay_on);
		MOTOR_PORT &= ~drive_output;
		_delay_us(drive_delay_off);
		distance -= 0.05;											// Arbitrary decrement
	}
}

void motors_turn_tank(char heading, char duty, double distance)
{
	//Left: MOTOR_1 REV, MOTOR_2 FWD
	//Right: MOTOR_1 FWD, MOTOR_2 REV

	double delay_on = ((double)duty / 100) * 500;			// Sets the on-time for the motor
	double delay_off = (500 - delay_on);					// Sets the off-time for the motor

	char output = (1 << MOTOR_B1) | (1 << MOTOR_EN1) | (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Default left

	if (heading == RIGHT)
	{
		output = (1 << MOTOR_A1) | (1 << MOTOR_EN1) | (1 << MOTOR_B2) | (1 << MOTOR_EN2);		// Right override
	}

	while (distance > 0)
	{
		MOTOR_PORT |= output;
		_delay_us(delay_on);
		MOTOR_PORT &= ~output;
		_delay_us(delay_off);
		distance -= 0.025;									// Arbitrary decrement
	}
}

// Car body

void motors_drive_car(char direction, char duty, double distance)
{
	// Todo: Not be lazy and actually implement PWM

	//Forward: MOTOR_A = HIGH, MOTOR_B = LOW
	//Reverse: MOTOR_A = LOW, MOTOR_B = HIGH
	//Brake: MOTOR_A = MOTOR_B

	double delay_on = ((double)duty / 100) * 500;// Sets the on-time for the motor
	double delay_off = (500 - delay_on);	// Sets the off-time for the motor

	char output = (1 << MOTOR_A1) | (1 << MOTOR_EN1);		// Default forward

	if (direction == REVERSE)
	{
		output = (1 << MOTOR_B1) | (1 << MOTOR_EN1);		// Reverse override
	}

	while (distance > 0)
	{
		MOTOR_PORT |= output;
		_delay_us(delay_on);
		MOTOR_PORT &= ~output;
		_delay_us(delay_off);
		distance -= 0.025;									// Arbitrary decrement
	}

	// Set motor 1 outputs low
	MOTOR_PORT &= ~((1 << MOTOR_EN1) | (1 << MOTOR_A1) | (1 << MOTOR_B1));
}

void motors_go_car(char direction, char heading, char duty, double distance)
{
	//Forward: MOTOR_A = HIGH, MOTOR_B = LOW
	//Reverse: MOTOR_A = LOW, MOTOR_B = HIGH
	//Brake: MOTOR_A = MOTOR_B

	//Left: MOTOR_A = HIGH, MOTOR_B = LOW
	//Reverse: MOTOR_A = LOW, MOTOR_B = HIGH
	// Empirically: 1200ms on / 800ms off

	double drive_delay_on = ((double) duty / 100) * 500;			// Sets the on-time for the motor
	double drive_delay_off = (500 - drive_delay_on);				// Sets the off-time for the motor

	char drive_output = (1 << MOTOR_A1) | (1 << MOTOR_EN1);			// Default forward
	char steering_output = (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Default left

	if (direction == REVERSE)
	{
		drive_output = (1 << MOTOR_B1) | (1 << MOTOR_EN1);			// Reverse override
	}
	else if (direction == NEUTRAL)
	{
		drive_output = 0;
	}
	else if (direction == BRAKE)
	{
		drive_output = (1 << MOTOR_A1) | (1 << MOTOR_B1) | (1 << MOTOR_EN1);
	}

	if (heading == RIGHT)
	{
		steering_output = (1 << MOTOR_B2) | (1 << MOTOR_EN2);		// Right override
	}
	else if (heading == CENTRE)
	{
		steering_output = 0;										// Centre override
	}

	while (distance > 0)
	{
		for (int i = 0; i > 4; i++)
		{
			if (i >= 2)
			{
				MOTOR_PORT &= ~steering_output;
			}
			else
			{
				MOTOR_PORT |= steering_output;
			}

			MOTOR_PORT |= drive_output;
			_delay_us(drive_delay_on);
			MOTOR_PORT &= ~drive_output;
			_delay_us(drive_delay_off);
		}

		distance -= 0.1;											// Arbitrary decrement
	}

	// Set motor 1 outputs low
	MOTOR_PORT &= ~((1 << MOTOR_EN1) | (1 << MOTOR_A1) | (1 << MOTOR_B1));
	// Set motor 2 outputs low
	MOTOR_PORT &= ~((1 << MOTOR_EN2) | (1 << MOTOR_A2) | (1 << MOTOR_B2));
}

void motors_turn_car(char heading, char duty, double distance)
{
	//Left: MOTOR_A = HIGH, MOTOR_B = LOW
	//Reverse: MOTOR_A = LOW, MOTOR_B = HIGH

	double delay_on = ((double)duty / 100) * 2000;			// Sets the on-time for the motor
	double delay_off = (2000 - delay_on);					// Sets the off-time for the motor

	char output = (1 << MOTOR_A2) | (1 << MOTOR_EN2);		// Default left

	if (heading == RIGHT)
	{
		output = (1 << MOTOR_B2) | (1 << MOTOR_EN2);		// Right override
	}

	while (distance > 0)
	{
		MOTOR_PORT |= output;
		_delay_us(delay_on);
		MOTOR_PORT &= ~output;
		_delay_us(delay_off);
		distance -= 0.1;									// Arbitrary decrement
	}

	// Set motor 2 outputs low
	MOTOR_PORT &= ~((1 << MOTOR_EN2) | (1 << MOTOR_A2) | (1 << MOTOR_B2));
}
