/*
 * commands.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

// The inputted commands are never going to be
// more than 8 chars long. Volatile for the ISR.
volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile unsigned char command_ready;

void copy_command();
void process_command();

#endif /* COMMANDS_H_ */
