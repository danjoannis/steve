#!/usr/bin/env python

import connect_io
import csv
import time
import io

sio = io.TextIOWrapper(io.BufferedRWPair(connect_io.ser, connect_io.ser))

thetime = time.strftime("%Y_%m_%d_%H%M%S")

with open('steve_log_%s.csv' % thetime, 'wb') as csvfile:
    logwriter = csv.writer(csvfile, delimiter=',')
    logwriter.writerow(['Timestamp','Distance'])
    while(1):
        sio.write(unicode("Q?U\r"))
        sio.flush()
        distance = sio.readline()
        print "%s" % distance
        logwriter.writerow(['%s' % time.strftime("%Y_%m_%d_%H%M%S"),distance])
	time.sleep(1)
