# This script will flash steve_io.hex to the Uno

avrdude -p m328p -c arduino -P /dev/ttyACM0 -U flash:w:/steve/steve_io/Release/steve_io.hex:a
