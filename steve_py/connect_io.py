#!/usr/bin/env python

import serial
 
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
print("Connecting to Arduino")
print(ser.name)
