# camera module

## data flow

each time the camera is activated it starts a 'session'

this is controlled from the web application

if the unit looses web-connection for X period - it will disable what is sensible (e.g. not GPS) and stop the session

this should be a long time - if the unit looses connection for half the track - it should remain active

if the unit then regains connection - it will reconnect and present the 'continue' or 'stop' options

## video files

the raw h.264 stream is saved to a file named after the session / data

we capture 1080p @ 30fps

this is fed directly into red5video which:

	* writes chunks out to the session video file
	

it also feeds the data into transcoder which resizes the video down to 400 x 300





## raspivid 

```
-?,   --help        : This help information
-w,   --width       : Set image width <size>. Default 1920
-h,   --height      : Set image height <size>. Default 1080
-b,   --bitrate     : Set bitrate. Use bits per second
                      (e.g. 10MBits/s would be -b 10000000)
-o,   --output      : Output filename <filename>
-v,   --verbose     : Output verbose information during run
-t,   --timeout     : Duration of video (in ms)
-d,   --demo        : Demo mode(cycle through range of camera
                      options, no capture)
-fps, --framerate   : Specify the frames per second to record
-e,   --penc        : Display preview image *after* encoding
                      (shows compression artifacts)
-p, --preview       : Preview window settings <'x,y,w,h'>
-f, --fullscreen    : Fullscreen preview mode
-n, --nopreview     : Do not display a preview window
-sh, --sharpness    : Set image sharpness (-100 to 100)
-co, --contrast     : Set image contrast (-100 to 100)
-br, --brightness   : Set image brightness (0 to 100)
-sa, --saturation   : Set image saturation (-100 to 100)
-ISO, --ISO         : Set capture ISO
-vs, --vstab        : Turn on video stablisation
-ev, --ev           : Set EV compensation
-ex, --exposure     : Set exposure mode (see Notes)
-awb, --awb         : Set AWB mode (see Notes)
-ifx, --imxfx       : Set image effect (see Notes)
-cfx, --colfx       : Set colour effect (U:V)
-mm, --metering     : Set metering mode (see Notes)
-rot, --rotation    : Set image rotation (0, 90, 180, 270)
-hf, --hflip        : Set horizontal flip
-vf, --vflip        : Set vertical flip
```

## links

---> this is the solution - websockets:

http://phoboslab.org/log/2013/09/html5-live-video-streaming-via-websockets



http://www.raspberrypi.org/phpBB3/viewtopic.php?f=43&t=44539
http://elinux.org/Rpi_Camera_Module#Video4Linux2
http://archlinuxarm.org/forum/viewtopic.php?f=31&t=6421

http://www.raspberrypi.org/phpBB3/viewtopic.php?t=44290&p=352910

http://justhackme.wordpress.com/2013/03/10/apples-http-live-streaming-in-flash/

http://raspberrypi.stackexchange.com/questions/7446/how-can-i-stream-h264-video-from-raspberry-camera-module-via-apache-nginx-for-re

http://www.raspberrypi.org/phpBB3/viewtopic.php?t=44104

http://www.raspberrypi.org/forum/viewtopic.php?f=43&t=45368&start=175