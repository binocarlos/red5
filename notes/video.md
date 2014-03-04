# video streaming

CONCLUSION

we need 2 PI's - we cannot record video via the GPU and at the same time resize video with the GPU

so - we need 2 GPU's


it turns out that transcoding (converting) the live input from the camera @ 1080p 30fps whilst saving it to a file will be a challenge.

The Pi comes with Hardware Accelerated H264 encoding.

H264 is a good option for our live broadcast layer but we need the video file much smaller than 1080p.

Here is the ideal pipeline:

```
raspivid | tee hdfile.h264 | extractframes | transcode --size 640x480 --format h264 | tee smallfile.h264 | upload --username X --key X --session X
```

This command will take live data from the camera and pipe it to tee -> local HD video file.

It then ends up in the extractframes step which will extract the current frame number from the video stream and emit it to the telemtry stream.

It then pipes data through the transcoder which will resize.

The resized video is saved to the local session SMALL video file.

It is then piped to the upload program.


## video frames

We somehow need a frame number from the video stream.  This so we can burn the framenumber into the telemtry stream for later synchronization.

This is done from the '--inline' command of raspivid which inserts SPS and PPS headers into the stream.

These are used by Apples HLS format (for live streaming).

We will use the headers that contain the frame number to determine what video frame the current telemtry stream applies to.

This is written into the telemtry stream:

e.g. telemetry stream with current video file as a value

```
VID:37837:GPS:4355
```

[this library](https://github.com/AndyA/psips) is a good source of reference for this

## transcoding

The PI has hardware accelerated h264 encode/decode.

The code to access this is called OpenMax.

You either have to write a program in C that uses the OpenMax or use g-streamer which has it built in.



## snow

this is gstreamer producing raw video and it being encoded into h264 using the hardware

```
raspivid -t 1000 -h 720 -w 1080 -fps 25 -hf -b 10000000 -o - | gst-launch-1.0 -v fdsrc ! omxh264dec ! omxh264enc ! filesink location=/dev/stdout > /home/pi/cam3.h264
```


raspivid -t 1000 -h 720 -w 1080 -fps 25 -hf -b 10000000 -o - | gst-launch-1.0 -v fdsrc ! omxh264dec ! videoscale ! video/x-raw-yuv,width=640,height=340 ! omxh264enc ! filesink location=/dev/stdout > /home/pi/cam3.h264

control-rate=1 target-bitrate=2500000 ! "video/x-h264,profile=high,width=704,height=576"
videoscale ! video/x-raw-yuv,width=178,height=100


## misc scripts


A command to stream video through gstreamer

```
raspivid -t 2000 -h 720 -w 1080 -fps 25 -hf -b 10000000 -o - | gst-launch-1.0 -v fdsrc ! decodebin ! videoconvert ! videoscale ! video/x-raw-yuv,width=640,height=340 ! omxh264enc ! filesink location=/dev/stdout > /home/pi/test.h264
```

raspivid -t 2000 -h 720 -w 1080 -fps 25 -hf -b 10000000 -o - | gst-launch-1.0 -v fdsrc ! decodebin ! omxh264enc ! filesink location=/dev/stdout > /home/pi/test.h264

```
gst-launch v4l2src device=/dev/video0 ! 'video/x-raw-yuv,width=640,height=480' !  x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=127.0.0.1 port=1234
```
```
gst-launch-1.0 -v fdsrc ! h264parse !  !  control-rate=1 
target-bitrate=1500000 ! "video/x-h264,profile=high,width=720,height=568" ! queue ! h264parse ! 
mux. matroskamux name=mux ! filesink location='out.mkv' 

```

server sink:

```
tcpserversink host=192.168.1.101 port=5000
```



## commands

checking the openmax installation:

```
gst-inspect-1.0 | grep OpenMAX
```

checking a module:

```
gst-inspect-1.0 videoconvert
```

## links

http://wiki.oz9aec.net/index.php/Raspberry_Pi_Camera

http://www.raspberrypi.org/forum/viewtopic.php?f=43&t=48300

http://emmanuelgranatello.blogspot.co.uk/2013/10/raspberry-pi-gstreamer-streaming-h264.html

http://stackoverflow.com/questions/7669240/webcam-streaming-using-gstreamer-over-udp/9579478#9579478

http://www.raspberrypi.org/forum/viewtopic.php?f=38&t=6852&start=200

http://emmanuelgranatello.blogspot.co.uk/2013/10/raspberry-pi-gstreamer-streaming-h264.html

http://www.roxlu.com/2013/002/converting-video-audio-using-avconv




http://www.raspberrypi.org/forum/viewtopic.php?f=70&t=25022&start=25




http://raspberrypi.stackexchange.com/questions/4226/how-can-i-use-my-pi-to-convert-a-video-audio-stream-in-real-time-to-another-form

http://raspberrypi.stackexchange.com/questions/245/are-there-hardware-incompatible-video-codecs

http://www.raspberrypi.org/archives/592

http://cgit.freedesktop.org/gstreamer/gst-omx/

http://www.raspberrypi.org/phpBB3/viewtopic.php?f=38&t=24741

http://www.raspberrypi.org/phpBB3/viewtopic.php?f=43&t=44982