#!/usr/bin/env python

import serial, io
 
try:
  ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
  print("Connected to Arduino")
  print(ser.name)
  sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
except:
  print "Arduino not found - is it plugged in?"
