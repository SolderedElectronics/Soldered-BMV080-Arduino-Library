/**
 **************************************************
 *
 * @file        simpleReading.ino
 * @brief       Example for simple reading of PM10, PM2.5 and PM1 concentrations
 *              and obstruction status using the BMV080 sensor in continuous mode.
 *
 *
 * @link        https://solde.red/333373
 *
 * @authors     Josip Šimun Kuči @ soldered.com
 ***************************************************/

 #include "BMV080-SOLDERED.h"

 BMV080 bmv080; // Create an instance of the BMV080 class
 #define BMV080_ADDR 0x57  // BMV080 default address
 
 void setup()
 {
     Serial.begin(115200);
 
     while (!Serial)
         delay(10); // Wait for Serial to become available.
 
     Wire.begin();
 
     if (bmv080.begin(BMV080_ADDR, Wire) == false)
     {
         Serial.println(
             "BMV080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
         while (1)
             ;
     }
 
     /* Initialize the Sensor (read driver, open, reset, id etc.)*/
     bmv080.init();
 
     /* Set the sensor mode to continuous mode */
     if (bmv080.setMode(BMV080_MODE_CONTINUOUS) == true)
     {
         Serial.println("BMV080 set to continuous mode");
     }
     else
     {
         Serial.println("Error setting BMV080 mode");
     }
 }
 
 void loop()
 {
     if (bmv080.readSensor())
     {
         float pm10 = bmv080.PM10();
         float pm25 = bmv080.PM25();
         float pm1 = bmv080.PM1();
 
         Serial.print("PM10: ");
         Serial.print(pm10);
         Serial.print("\t");
         Serial.print("PM2.5: ");
         Serial.print(pm25);
         Serial.print("\t");
         Serial.print("PM1: ");
         Serial.print(pm1);
 
         if (bmv080.isObstructed() == true)
         {
             Serial.print("\tObstructed");
         }
 
         Serial.println();
     }
     delay(100);
 }
 