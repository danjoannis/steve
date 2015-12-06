#!/usr/bin/env python

import serial
 
ser = serial.Serial('/dev/ttyACM0', 38400)
print("Connecting to Arduino")
