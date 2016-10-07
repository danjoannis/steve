#!/usr/bin/env python

import connect_io, os, io, time, threading, netifaces, urllib2

# Variable definitions
exitFlag = 0
distanceFront = 0
cpuTemp = 0

# Classes
class ipCheck (threading.Thread):
  def __init__(self, threadID, name, counter):
    threading.Thread.__init__(self)
    self.threadID = threadID
    self.name = name
    self.counter = counter
  def run(self):
    print "Starting " + self.name
    while 1:
      # Do work here
      try:
        setSteveIp()
      except:
        print "Error updating IP"
      time.sleep(10)
      if exitFlag:
        self.name.exit()
    print "Exiting " + self.name

# Functions
def setSteveIp():
  netifaces.ifaddresses('wlan0')
  ip = netifaces.ifaddresses('wlan0')[2][0]['addr']
  urllib2.urlopen("http://danjoannis.com/steve/set_steve.php?ip=" + ip).read()
  
# Init
thread1 = ipCheck(1, "ipCheck-1", 1)

# Main
thread1.start()
