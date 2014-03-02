arduino
-------

The sensor board is an arduino with 3 sensors connected:

 * GPS - UP501
 * Compass - HMC5883L
 * Accel / Gyro - MPU-6050

## GPS

The GPS is connected to pins RX=3 - TX=4

```
SoftwareSerial gpsSerial(3, 4);
```

We set it to 10Hz and small dataset:

```
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

void setupGPS()
{
  // setup the GPS UNIT @ 9600
  gpsSerial.begin(9600);
  delay(200);
  // ask the GPS for a basic NMEA sentence (as we are wanting them quickly)
  gpsSerial.println(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  delay(200);
  // tell the GPS to give us sentences 10 times per second
  gpsSerial.println(PMTK_SET_NMEA_UPDATE_10HZ);
  delay(200);
}
```

The sensor gives us NMEA sentences.

## Compass & Accel / Gryo

Both boards are connected to the Arduino on the I2C bus (A4 & A5).

We use the custom libraries from [this repo](https://github.com/jrowberg/i2cdevlib) to speak to both chips.

We get data from these units as it arrives.

## licence

MIT