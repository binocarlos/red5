//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// red5 GPS code v0.0.1
//
// GPS library for the red5 sensor board
//
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#include "Arduino.h"
#include "Wire.h"
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "HMC5883L.h"
#include "MPU6050.h"


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// GPS
//
// RX, TX
SoftwareSerial gpsSerial(3, 4);

#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// String buffer for the current GPS sentence
String nmeaSentence;

void setupGPS()
{
  Serial.println("------------------------------------------------------");
  Serial.println("Starting the GPS");
  Serial.println("------------------------------------------------------");
  
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

String getSplitValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void handleGPS()
{
  while(gpsSerial.available() > 0){
    char recieved = gpsSerial.read();
    
    if(recieved == '\n')
    {
      Serial.println("GPS:" + nmeaSentence);
      // check to see if we have active GPS
      String checkactive = getSplitValue(nmeaSentence, ',', 6);
      if(checkactive=="W")
      {
//        gpsBrightState = !gpsBrightState;
      }
      else
      {
//        gpsBrightState = HIGH; 
      }
//      digitalWrite(gpsBrightPin, gpsBrightState);
      nmeaSentence = "";
    }
    else{
      nmeaSentence += recieved;
    }
  }
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// COMPASS
//
HMC5883L mag;
int16_t mx, my, mz;

void setupCompass()
{
  Serial.println("------------------------------------------------------");
  Serial.println("Starting the Compass");
  Serial.println("------------------------------------------------------");

  mag.initialize();

  Serial.println("Testing device connections...");
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
}

void handleCompass()
{
	mag.getHeading(&mx, &my, &mz);
	Serial.println("MAG:");
  Serial.print(mx); Serial.print("\t");
  Serial.print(my); Serial.print("\t");
  Serial.print(mz); Serial.print("\t");
  Serial.print("\n");
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// ACCELGRYO
//
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setupAccelGyro()
{
  Serial.println("------------------------------------------------------");
  Serial.println("Starting the AccelGyro");
  Serial.println("------------------------------------------------------");

  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void handleAccelGyro()
{
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	//accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// MAIN
//

              
void setup()  
{
  Serial.begin(57600);
  delay(2000);
  setupGPS();
  Wire.begin();
  setupCompass();
  setupAccelGyro();
}

void loop() 
{
  handleGPS();
  handleCompass();
  handleAccelGyro();
} 
