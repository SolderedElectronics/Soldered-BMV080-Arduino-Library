/**
 **************************************************
 *
 * @file        BMV080-SOLDERED.h
 * @brief       Header wrapper file for Bosch BMV080 sensor.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors    Josip Šimun Kuči @ soldered.com
 ***************************************************/

 #ifndef BMV080_SOLDERED_H
 #define BMV080_SOLDERED_H

 #include "BMV080Wrapper/BMV080Wrapper.h"
 #include "BMV080Wrapper/BMV080WireBus.h"
 
 // The BMV080 Bosch API requires a larger than usual stack size
 // In particular, bmv080_serve_interrupt is the culprit.
 // If we are an ESP32 architecture, then we need to increase the loop stack size
 // to 60KB. This is because the ESP32 has a 32KB stack size by default.
 #if defined(ESP32)
 SET_LOOP_TASK_STACK_SIZE(60 * 1024); // 60KB
 #endif
 

 class BMV080 : public BMV080Core
 {
   public:
     /**
      * @brief Begins the Device with I2C as the communication bus
      *
      * This method initializes the I2C bus and sets up communication with the BMV080 sensor.
      *
      * @param address I2C device address to use for the sensor
      * @param wirePort Wire port to use for I2C communication
      * @return True if successful, false otherwise
      */
     bool begin(const uint8_t address = BMV080_DEFAULT_ADDRESS, TwoWire &wirePort = Wire)
     {
         // Setup Arduino I2C bus
         i2c.init(wirePort, address);
         i2c.setByteOrder(0); // MSB first (for compatibility)

         // Begin the sensor
         wireBusError_t rc = BMV080Core::begin(&i2c);

         return rc == wireBusOK && isConnected();
     }
 
     /* @brief Checks if the Device is connected
     * @return True if the sensor is connected, false otherwise
     */
    bool isConnected()
    {
        return i2c.ping() == wireBusOK;
    }

    private:
    BMV080WireBus i2c;
};

#endif
