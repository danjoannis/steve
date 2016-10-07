#!/bin/sh
sleep 40
cd /steve/steve_py
nohup sudo python watchdog.py &
sleep 5
nohup sudo python steve_web.py &
