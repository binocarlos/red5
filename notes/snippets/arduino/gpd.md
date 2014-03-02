```
#define PMTK_SET_NMEA_38400 "$PMTK251,38400*27"
#define PMTK_SET_NMEA_57600 "$PMTK251,57600*2C"
#define PMTK_SET_NMEA_115200 "$PMTK251,115200*1F"
void setup()
{
Serial.println("Config GPS...");
mySerial.begin(9600);
mySerial.println(PMTK_SET_NMEA_57600);
delay(100);
mySerial.end();
delay(1000);
mySerial.begin(57600);
delay(1000);
do other stuff
}
```