/*
 * util.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Daniel
 */

#include "util.h"
#include "uart.h"

void uart0_itoaWrite(int n)
{
	int i, sign;
	char s[5];

	if ((sign = n) < 0) //determines if negative
		n = -n;

	i = 0;
	do
	{
		s[i++] = n % 10 + '0'; //converts unit to base 10
	} while ((n /= 10) > 0); // delete it

	if (sign < 0)
		s[i++] = '-'; //appends minus sign if negative

	s[i] = '\0';
	my_reverse(s);
	uart0_putString(s);
}

void my_reverse(char s[])
{

	volatile int i, j, len;
	j = 0;

	len = my_strlen(s);

	volatile char tmp[len]; //Temporary array

	for (int i = len; i > 0; i--)
	{ //Starts from end of input array
		tmp[j] = s[i - 1]; //And stores from beginning of temp array
		j++;
	}

	for (i = 0; i < len; i++)
	{
		s[i] = tmp[i]; //Then stores temp back into input array
	}

}

int my_strlen(char s[])
{

	int i = 0;

	while (s[i] != '\0')
	{ //Will go through array until null character
		i++; //This is the strings length
	}

	return i;
}

