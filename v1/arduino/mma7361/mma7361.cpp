//
//    FILE: dht.cpp
// VERSION: 0.1.05
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//
// DATASHEET: 
//
// HISTORY:
// 0.1.05 fixed negative temperature bug (thanks to Roseman)
// 0.1.04 improved readability of code using DHTLIB_OK in code
// 0.1.03 added error values for temp and humidity when read failed
// 0.1.02 added error codes
// 0.1.01 added support for Arduino 1.0, fixed typos (31/12/2011)
// 0.1.0 by Rob Tillaart (01/04/2011)
// inspired by DHT11 library
//

#include "mma7361.h"

#define TIMEOUT 10000

/////////////////////////////////////////////////////
//
// PUBLIC
//


void mma7361::setup(uint8_t x, uint8_t y, uint8_t z, uint8_t sl, uint8_t gs)
{
    mXpin = x;
    mYpin = y;
    mZpin = z;
    mEnablepin = sl;
    mConfigpin = gs;

    pinMode(mEnablepin, OUTPUT);
    digitalWrite(mEnablepin, HIGH);

    // Set the precision for 6g mode
    //
    pinMode(mConfigpin, OUTPUT);
    digitalWrite(mConfigpin, LOW);

    // Activate the x/y/z pins
    //
    pinMode(mXpin, INPUT);
    pinMode(mYpin, INPUT);
    pinMode(mZpin, INPUT);

    calibrate();

}

int mma7361::mapvalue(int value)
{
    return map(value, 0, 1024, -800, 1600);
}

void mma7361::calibrate()
{

  // Wait to ensure device is powered and set
  //
  delay(100);

  // How many measurements to use in calibration
  const int count = 1000;

  // Grab a 1000 measurements and average
  //
  float   sum  = 0;
  for (int i = 0; i < count;i++)
  {
    sum += mapvalue(analogRead(mXpin));
    sum += mapvalue(analogRead(mYpin));
  }
  mOffset = sum / (count * 2);
}

// return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
void mma7361::update()
{
    const int AdcRx = analogRead(mXpin);
    const int AdcRy = analogRead(mYpin);
    const int AdcRz = analogRead(mZpin);

    // Remap to G
    //
    const float Gx = mapvalue(AdcRx) - mOffset;
    const float Gy = mapvalue(AdcRy) - mOffset;
    const float Gz = mapvalue(AdcRz) - mOffset;

    // See http://www.starlino.com/imu_guide.html

    // See http://code.google.com/p/mma7361-library/

    // See http://www.freescale.com/files/sensors/doc/data_sheet/MMA7361L.pdf

    // Vector magnitude
    //
    const float mag = sqrt((Gx*Gx) + (Gy*Gy) + (Gz*Gz));

    // Make a unit vector
    //
    mValueX = Gx / mag;
    mValueY = Gy / mag;
    mValueZ = Gz / mag;
}

//
// END OF FILE
//