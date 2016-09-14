#!/usr/bin/env python

import connect_io, os, time, io, warehouse
from bottle import route, run, template

def cpu_temp():
  dev = os.popen('/opt/vc/bin/vcgencmd measure_temp')
  cpu_temp = dev.read()[5:-3]
  return cpu_temp

@route('/time')
def pi_time():
  return time.strftime("%c")

@route('/cputemp')
def temp():
  return warehouse.cpuTemp

@route('/distance_front')
def distance_front():
  return warehouse.distanceFront

@route('/drive/<direction>/<heading>/<duty>')
def drive(direction, heading, duty):
  command = "D="
  if duty == "0":
    command += "S"
  else:
    command += direction
    command += heading
    command += duty
  command += "\r"
  connect_io.sio.write(unicode(command))
  connect_io.sio.flush()
  print(command)

@route('/')
def index():
  return template('main.html')

run(host='0.0.0.0', port=80)

os.system('flite -voice awb -t "Steve is now online."')
