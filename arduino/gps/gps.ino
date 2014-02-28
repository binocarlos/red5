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
#include <SoftwareSerial.h>

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
// MAIN
//

              
void setup()  
{
  Serial.begin(57600);
  delay(2000);
  setupGPS();
}

void loop() 
{
  handleGPS();
} 
