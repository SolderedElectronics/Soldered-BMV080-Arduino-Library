/**
 **************************************************
 *
 * @file        InterruptTrigger.ino
 * @brief       Demonstrates how to use hardware interrupt of the sensor to get readings
 *
 *              Example demonstrates how to setup an interrupt triggered by the
 *              BMV080's IRQ pin to get readings. Sensor is set in continuous mode.
 *
 *              Note: Hardware interrupt cannot be used as trigger in duty cycling mode! 
 *
 *
 * @link        https://solde.red/333373
 *
 * @authors     Dino Ragač @ soldered.com
 ***************************************************/

#include "BMV080-SOLDERED.h"

BMV080 bmv080;              // Create an instance of the BMV080 class
#define BMV080_ADDR 0x57    // BMV080 default I2C address

#define IRQ_PIN 13          // Declare interrupt pin

bool triggered = false;     // Interrupt flag

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

  // Set the sensor mode to continuous mode
  // The hardware interrupt of the BMV080 sensor unit cannot be used as trigger 
  // in duty cycling mode.
  if(bmv080.setMode(BMV080_MODE_CONTINUOUS) == true)
  {
    Serial.println("BMV080 set to continuous mode");
  }
  else
  {
    Serial.println("Error setting BMV080 mode");
  }

  enable_external_interrupt(true);    // Enable external interrupt handling for the IRQ pin
}

void loop()
{
  // Check if interrupt flag was set
  if (triggered == true)
  {
    Serial.println("Interrupt triggered");
    triggered = false; // Reset the interrupt flag

    // Keep reading sensor data
    do
    {
      Serial.print("Reading BMV080: ");
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
    } while (digitalRead(IRQ_PIN) == LOW);
  }
  delay(150);
  Serial.print(".");
}

void enable_external_interrupt(bool enable)
{
  int checkPin = digitalPinToInterrupt(IRQ_PIN);

  if (checkPin == -1) 
  {
    Serial.println("Not a valid interrupt pin!");
  }
  else 
  {
    Serial.println("Valid interrupt pin.");
  }

  pinMode(IRQ_PIN, INPUT_PULLUP);    // Configure IRQ pin as input with internal pull-up resistor

  if (enable)
  {    // Enabel external interrupt 
    attachInterrupt(digitalPinToInterrupt(IRQ_PIN), ISR_handler, FALLING );  
  }
  else
  {    // Disable external interrupt
    detachInterrupt(digitalPinToInterrupt(IRQ_PIN) );
  }
}

void ISR_handler(void)
{
  // Set interrupt flag
  triggered = true;
}
