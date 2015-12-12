#!/usr/bin/env python

import connect_io

command="D=\x00\x01\x55\x40\r"
print command
connect_io.ser.write(command)
