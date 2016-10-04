#!/usr/bin/env python

import connect_io, os, time, io, urllib2, netifaces, watchdog
from bottle import route, run, template

def cpu_temp():
  dev = os.popen('/opt/vc/bin/vcgencmd measure_temp')
  cpu_temp = dev.read()[5:-3]
  return cpu_temp

@route('/poweroff')
def power_off():
  os.system("sudo poweroff")

@route('/time')
def pi_time():
  return time.strftime("%c")

@route('/cputemp')
def temp():
  return warehouse.cpuTemp

@route('/distance_front')
def distance_front():
  return warehouse.distanceFront

@route('/vbatt')
def getDistanceFront():
  connect_io.sio.write(unicode("Q?B\r"))
  connect_io.sio.flush()
  return connect_io.sio.readline()

@route('/enable_motors')
def enableMotorPower():
  connect_io.sio.write(unicode("PME\r"))
  connect_io.sio.flush()
  print("INFO: Motors enabled")
  
@route('/disable_motors')
def disableMotorPower():
  connect_io.sio.write(unicode("PMD\r"))
  connect_io.sio.flush()
  print("INFO: Motors disabled")

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
  connect_io.sio.flush()
  connect_io.sio.write(unicode(command))
  connect_io.sio.flush()
  print(command)

@route('/')
def index():
  return template('main.html')

# os.system('flite -voice awb -t "Steve is going online."')

netifaces.ifaddresses('wlan0')
ip = netifaces.ifaddresses('wlan0')[2][0]['addr']
urllib2.urlopen("http://danjoannis.com/steve/set_steve.php?ip=" + ip).read()

run(host='0.0.0.0', port=80)
