#!/usr/bin/env python

import connect_io, os, time, io
from bottle import route, run, template

sio = io.TextIOWrapper(io.BufferedRWPair(connect_io.ser, connect_io.ser))

def cpu_temp():
  dev = os.popen('/opt/vc/bin/vcgencmd measure_temp')
  cpu_temp = dev.read()[5:-3]
  return cpu_temp

@route('/time')
def pi_time():
  return time.strftime("%c")

@route('/cputemp')
def temp():
  return cpu_temp()

@route('/distance_front')
def distance_front():
  sio.write(unicode("Q?U\r"))
  sio.flush()
  return sio.readline()

@route('/')
def index():
  return template('main.html')

run(host='0.0.0.0', port=80)
