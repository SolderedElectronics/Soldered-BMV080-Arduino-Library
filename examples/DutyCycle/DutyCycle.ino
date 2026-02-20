/**
 **************************************************
 *
 * @file        DutyCycle.ino
 * @brief       Demonstrates how to use the sensor in "duty cycle mode" to
 *              get PM readings every 20 seconds.
 *
 *
 * @link        https://solde.red/333373
 *
 * @authors     Dino Ragač @ soldered.com
 ***************************************************/

 #include "BMV080-SOLDERED.h"

 BMV080 bmv080;             // Create an instance of the BMV080 class
 #define BMV080_ADDR 0x57   // BMV080 default address

void setup()
{
  Serial.begin(115200);

  while (!Serial) delay(10);  // Wait for Serial to become available

  Wire.begin();

  // Attempt to initialize the sensor via I2C
  if (bmv080.begin(BMV080_ADDR, Wire) == false) 
  {
    Serial.println("BMV080 not detected");
    while (1)
    ;
  }
  Serial.println("BMV080 found!");

  // Initialize the sensor
  if (bmv080.init())
  {
    Serial.println("BMV sensor initialized");
  }
  else
  {
    Serial.println("BMV initialization failed");
    while (1)
    ;
  }

  // Set the sensor Duty Cycling Period (seconds)
  uint16_t duty_cycling_period = 20;

  if(bmv080.setDutyCyclingPeriod(duty_cycling_period) == true)
  {
    Serial.println("BMV080 set to 20 second duty cycle period.");
  }
  else
  {
    Serial.println("Error setting BMV080 duty cycle period.");
  }

  // Set the sensor mode to Duty Cycle mode
  if(bmv080.setMode(BMV080_MODE_DUTY_CYCLE) == true)
  {
    Serial.println("BMV080 set to Duty Cycle mode");
  }
  else
  {
    Serial.println("Error setting BMV080 mode");
  }
}

void loop()
{
  // Attempt to get reading
  if (bmv080.readSensor())
  {
    float pm25 = bmv080.PM25();

    Serial.print(pm25);

    if (bmv080.isObstructed() == true)
    {
      Serial.print("\tObstructed");
    }

    Serial.println();
  }
  delay(1000);
}
