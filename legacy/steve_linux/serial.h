/*
 * serial.h
 *
 *  Created on: Dec 12, 2015
 *      Author: Daniel
 */

#ifndef SERIAL_H_
#define SERIAL_H_

int open_port(void);
int configure_port(int fd);
int query_modem(int fd);

#endif /* SERIAL_H_ */
