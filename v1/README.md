#install log

##Arduino IDE
installed [Enhanced IDE](http://arduino.cc/forum/index.php?topic=118440.0)


##GPS Unit

[Created circuit](http://www.adafruit.com/index.php?main_page=popup_image_additional&pID=660&pic=1&products_image_large_additional=images/large/ID660bb_LRG.jpg)

saved -> arduino/gps/fasttraxup501/setbaudrate

GPS data now coming from serial terminal - 9600 baud for GPS unit -> 57600 for Serial to PC

##Raspberry PI

[Downloaded latest Raspbian](http://www.raspberrypi.org/downloads)

Installed image with WindiskImager

PI powered from USB hub -> also data from same hub

Booted raspberry PI with HDMI and keyboard plugged into USB hub

Disabled GUI
Enabled SSH

logged in -> set PI password

DHCP for the moment -> 192.168.1.15

SSH from windows from now on


##Install node.js on PI

[source](http://www.raspberrypi.org/phpBB3/viewtopic.php?f=63&t=30265)

made src/bin/installnode.sh script for this

## USB

plugged in wifi key -> PI
usb camera -> Hub

	lsusb

shows the devices

## Install Fritzring

[Cool program for schematics](http://fritzing.org/download/)

## Install Arduino Libraries

For information on installing libraries, see: http://arduino.cc/en/Guide/Libraries

## Install Arduino Nano
Downloaded http://www.ftdichip.com/Drivers/VCP.htm

http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave

http://justpushbuttons.com/blog/?p=376

Dosn't work

## Made neater backing board
Cut some cardboard and now there is a much better backing for the setup

## Plan

1. Raspberry Pi as Wireless Access Point (192.168.15.1)
2. PI with 3 Dongle onto Tinterwebs
3. Pi now router
4. Ethernet onto local network for testing (192.168.1.15)
5. USB bus
	1. Arduino
		1. GPS
		2. Accelerometer
		3. Compass
		4. Gyro (purchase)
		5. LED's
	2. USB Camera
		1. fast resize control and gzip etc
		2. upload over sockets
		3. backend script to capture
	3. 3 dongle
6. Audio
	1. GPS on/off/beeps
	2. Recording sessions on/off/status
7. LED
	1. GPS quality
	2. 3G quality
	3. Accelerometer g's
	4. on/off
	5. Recording status
8. Firmata node.js control
9. Website with basic auth
10. viewing & control page socket.io -> node.js -> PI -> arduino -> ting

## Raspberry PI Access point (Internal wireless lan)

Hooked up manual control of PI