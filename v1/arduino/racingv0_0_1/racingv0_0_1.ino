//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Digger Racing v0.0.1
//
// The core arduino sensor library
//
// [Arduino] -- diggerid / request --> [Pi] -- proxy --> [Digger] -- reception --> [Supplier] -- radio --> [Subscribers]
//
// [Web Client] -- radio packet --> [socket.io] --> [switchboaard] --> [PI] --> [Arduino]
//
// We are sending digger requests back and forth - perhaps we encode them different for the PI -> arduino step to save JSON parsing
//
// Licence MIT
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <mma7361.h>

// this is for when we get a compass working
//#include <Comp6DOF_n0m1.h>
//#include <Wire.h>
//#include <HMC.h>

// A4 (SDA), A5 (SCL)


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Accelerometer
//


mma7361 accelerometer;

const int accelGSelectPin = 10;

void setupAccelerometer()
{
  Serial.println("------------------------------------------------------");
  Serial.println("Starting the Accelerometer");
  Serial.println("------------------------------------------------------");
  
  accelerometer.setup(A0,//x
                      A1,//y
                      A2,//z
                      11,//sleep
                      10);//gselect
  delay(200);
  digitalWrite(accelGSelectPin, LOW);
  delay(200);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// 6dof
//

//Comp6DOF_n0m1 sixDOF;

void setupSensors()
{
  Serial.println("------------------------------------------------------");
  Serial.println("Starting the 6DOF");
  Serial.println("------------------------------------------------------");
  setupAccelerometer();
}

int x,y,z;

void handleSensors()
{  
  accelerometer.update();
  
  Serial.print("ACC:");
  Serial.print(accelerometer.x());
  Serial.print(" ");
  Serial.print(accelerometer.y());
  Serial.print(" ");
  Serial.print(accelerometer.z());
  Serial.print("\n");

  
//  sixDOF.compCompass(x, y, z, accelerometer.x(), accelerometer.y(), accelerometer.z(), false);

//  Serial.print("RPY:");
//  Serial.print(sixDOF.roll()/100); 
//  Serial.print(sixDOF.pitch()/100);      
//  Serial.print(sixDOF.yaw()/100);   
//  Serial.print("\n");
  
//  sixDOF.compCompass(-(z), -(x), y, -(accelerometer.z()), -(accelerometer.x()), accelerometer.y(), true);

//  float compHeading = sixDOF.atan2Int(sixDOF.yAxisComp(), sixDOF.xAxisComp());
//  compHeading = compHeading /100;
//  compHeading += 180;  
  
//  Serial.print("COMPASS:");
//  Serial.print (compHeading);
//  Serial.print("\n");
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// GPS
//

SoftwareSerial gpsSerial(2, 3);

#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// control the led for GPS updates
const int gpsBrightPin =  8;
int gpsBrightState = LOW;

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

String getValue(String data, char separator, int index)
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

      
      // output the GPS data to serial
      Serial.println("GPS:" + nmeaSentence);
      String checkactive = getValue(nmeaSentence, ',', 6);
      if(checkactive=="W")
      {
        gpsBrightState = !gpsBrightState;        
      }
      else
      {
        gpsBrightState = HIGH; 
      }
      digitalWrite(gpsBrightPin, gpsBrightState);
      nmeaSentence = "";
      
      handleSensors();
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
// MAIN
//


void setup()  
{
  Serial.begin(57600);
  delay(200);
  setupGPS();
  setupSensors();
}

void loop() 
{
  handleGPS();
} 
