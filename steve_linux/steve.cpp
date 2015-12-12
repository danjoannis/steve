/*
 * steve.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: Daniel
 */

#include <iostream>		// Streams

#include "serial.h"		// My serial library

using namespace std;

int main()
{
	cout << "Hello world!" << endl;

	cout << "Connecting to Arduino: ";

	if (open_port() == 0)
	{
		cout << "OK!" << endl;
	}
	else
	{
		cout << "ERROR!" << endl;
	}

	return 0;
}
