import netifaces, urllib2

netifaces.ifaddresses('wlan0')
ip = netifaces.ifaddresses('wlan0')[2][0]['addr']
urllib2.urlopen("http://danjoannis.com/steve/set_steve.php?ip=" + ip).read()
