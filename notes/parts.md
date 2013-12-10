parts
-----

Parts list for mark 2

## Minimal

This build is for one camera / sensor + Internet module

 * [Raspberry PI + SD](http://uk.farnell.com/jsp/search/productdetail.jsp?sku=2334982)
 * [Camera Board](http://uk.farnell.com/raspberry-pi/rpi-camera-board/raspberry-pi-camera-board-5mp/dp/2302279)

## Research

Things to look at for future builds

## Development

Things needed by a developer to replicate the system

Minimal + 

 * [HDMI Cable](http://uk.farnell.com/pro-signal/psg02574/lead-hdmi-to-dvi-2m/dp/1813133)
 * [Power](http://uk.farnell.com/raspberry-pi-psu/rpi-psu-uk-mk1/power-supply-raspberry-5v-1a-uk/dp/2254792)

## mark 2 telemetry system

this is an overview of the digger racing telemetry system version 2.0 - codename: Red5

## overview

the first prototype was a succesful proof of concept - we have working in v1:

 * GPS chip
 * accellerometer chip
 * local data capture (SD Card)
 * internet Broadcast  (GPRS modem)
 * live telemetry screen (socket.io from server)

the second version will focus on adding a camera to the basic data stream.

### v1 components

#### GPS Chip

#### GPS LED

#### Accelerometer Chip

#### Sensor Controller (Arduino)

#### Main Controller (PI)

#### GPRS Modem

#### USB Hub - external power

#### Power source for hub

#### Web application

### v2 additions

#### Camera module (+ infrared)

 * [IR camera](http://uk.rs-online.com/web/p/video-modules/7902811/)
 * [camera](http://raspberrypi.rsdelivers.com/product/raspberry-pi/camera-module/raspberry-pi-hd-video-camera-module/7757731.aspx)



## getting the PI online

 * http://www.sbprojects.com/projects/raspberrypi/mobile.php
 * http://www.instructables.com/id/Raspberry-Pi-as-a-3g-Huawei-E303-wireless-Edima/
 * http://www.mathewjenkinson.co.uk/raspberry-pi-and-3g-dongle/