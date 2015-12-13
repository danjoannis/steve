/*
 * serial.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: Daniel
 */

//#include <unistd.h>		// UNIX standard function definitions
#include <fcntl.h>		// File control definitions
//#include <errno.h>		// Error number definitions
#include <termios.h>	// POSIX terminal contorl definitions
#include <time.h>		// Time calls
#include <string.h>		// Strings
#include <iostream>

#include "serial.h"

using namespace std;

int open_port(void)
{
	int fd; // file description for the serial port

	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);

	if(fd == -1) // if open is unsucessful
	{
		cout <<  "Unable to open /dev/ttyACM0" << endl;
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		cout << "Port is open" << endl;
	}

	return(fd);
} //open_port

int configure_port(int fd)      // configure the port
{
	struct termios port_settings;      // structure to store the port settings in

	cfsetispeed(&port_settings, B38400);    // set baud rates
	cfsetospeed(&port_settings, B38400);

	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;

	tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
	return(fd);

} //configure_port

int query_modem(int fd)   // query modem with an AT command
{
	char n;
	fd_set rdfs;
	struct timeval timeout;

	// initialise the timeout structure
	timeout.tv_sec = 10; // ten second timeout
	timeout.tv_usec = 0;

	//Create byte array
	unsigned char send_bytes[] = { 0x02, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x01, 0x21, 0x03};


	write(fd, send_bytes, 13);  //Send data

	// do the select
	n = select(fd + 1, &rdfs, NULL, NULL, &timeout);

	// check if an error has occured
	if(n < 0)
	{
	}
	else if (n == 0)
	{
	}
	else
	{
	}

	return 0;

} //query_modem


