#!/usr/bin/env python

import connect_io, os, io, time, threading

# Variable definitions
exitFlag = 0
distanceFront = 0
cpuTemp = 0

# Classes
class getStats (threading.Thread):
  def __init__(self, threadID, name, counter):
    threading.Thread.__init__(self)
    self.threadID = threadID
    self.name = name
    self.counter = counter
  def run(self):
    print "Starting " + self.name
    while 1:
      getCpuTemp()
      getDistanceFront()
      if exitFlag:
        self.name.exit()
    print "Exiting " + self.name

# Functions
def getCpuTemp():
  dev = os.popen('/opt/vc/bin/vcgencmd measure_temp')
  global cpuTemp
  cpuTemp = dev.read()[5:-3]

def getDistanceFront():
  connect_io.sio.write(unicode("Q?U\r"))
  connect_io.sio.flush()
  global distanceFront
  distanceFront = connect_io.sio.readline()
  
# Init
thread1 = getStats(1, "GetStats-1", 1)

# Main
thread1.start()