// 
//    FILE: dht.h
// VERSION: 0.1.05
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
// 

#ifndef dht_h
#define dht_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define MMA7361_LIB_VERSION     "0.1.01"
#define MMA7361_OK               0

class mma7361
{
public:
        
        void setup(uint8_t x, uint8_t y, uint8_t z, uint8_t sl, uint8_t gs);
        void update();
        int mapvalue(int value);

        inline float x() const
        {
          return mValueX;
        }

        //! @brief Access the raw data
        //!
        //! @return the position
        //!
        inline float y() const
        {
          return mValueY;
        }

        //! @brief Access the raw data
        //!
        //! @return the position
        //!
        inline float z() const
        {
          return mValueZ;
        }




protected:

        void calibrate();        
        
private:

        float mOffset;
        float mValueX;
        float mValueY;
        float mValueZ;

        uint8_t mXpin;
        uint8_t mYpin;
        uint8_t mZpin;
        uint8_t mEnablepin;
        uint8_t mConfigpin;
};
#endif
//
// END OF FILE
//