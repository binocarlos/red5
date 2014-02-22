# data flow

## telemetry values

GPS @ 10Hz (chip configurable)

G

 * long 		(G1)
 * lat 			(G2)
 * speed 		(G3)
 * time 		(G4)

Accelerometer @ 10Hz (sample rate)

A

 * X				(A1)
 * Y        (A2)
 * Z        (A3)

Compass @ ?hz

 * degrees  (C1)

Gryo @ ?Hz

 * yaw      (Y1)
 * pitch    (Y2)
 * roll     (Y3)

Temperature @ 1Hz

 * degrees  (T1)

Humidity @ 1Hz

 * unit used(H1)

## arduino

runs in a loop collecting the above

## serial format

each value emitted to the PI has a code then '=' then the value

values are seperated by :

here is an example of GPS long followed by Temp degrees:

```
G1=343434343434:T1=3344
```

## time

the gps will be writing timecodes @ 10hz

other values are assumed to be the timecode most recently registered

for example - the 2 gryo values will both have timecode 15:

(G4 is the time code)

```
G4=15:Y1=1:Y2=2
```

## PI decoding

the PI is collecting the serial streams from X number of arduino sensor boxes.

Each stream will travel via the red5-arduino-stream npm module

This will decode the above serial format into requests for lem.

## lem values

the car id is the start of the key - the name of the field (as decoded from the serial format) is the rest of the key.

the PI will create a lem stream collection that it will pipe new values to.

the online system is reacting to the new lem values arriving

the local system is saving the values to a local leveldb

## camera

the same time as the telemetry is arriving - the camera is recording live

ffmpeg is resizing the video as well as the raw stream being saved to sdcard

the resized video stream is piped online alongside the lem data stream

## transport

we can use axon / https streams or web-sockets to get the data stream to the server

there should be the same data transport for the data as the video - they should be interleaved and arrive together at the server

## server

the server is taking the raw data flow and decoding the video / lem data

the central pub/sub server is setup with connected viewers for that car

each data event (video/telemetry packet) is broadcast out via the pub/sub server

also the data is sent to the backend storage for saving and later retrieval


## car id

the id of the car needs to be controlled somehow from outside input

## general box control

the wifi key on the box (when in active mode) should be broadcasting a wifi network.

joining the network lets you see video in HD that has been saved - it lets you configure the box also

