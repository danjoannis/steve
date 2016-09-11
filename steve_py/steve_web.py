import os, time
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
  return cpu_temp()

@route('/')
def index():
  return template('main.html')

run(host='0.0.0.0', port=80)
