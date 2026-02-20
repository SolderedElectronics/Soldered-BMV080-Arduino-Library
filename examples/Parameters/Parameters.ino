/**
 **************************************************
 *
 * @file        Parameters.ino
 * @brief       Demonstrates reading and writing of configurable sensor parameters.
 *
 *              This example shows how to access and modify the adjustable settings
 *              of the sensor, including: volumetric mass density, integration time,
 *              distribution id, obstruction detection, vibration filtering and
 *              measurement algorithm.
 *

 *
 * @link        https://solde.red/333373
 *
 * @authors     Dino Ragač @ soldered.com
 ***************************************************/

#include "Wire.h"
#include "BMV080-SOLDERED.h"

BMV080 bmv080;              // Create and instance of the BMV080 class
#define BMV080_ADDR 0x57    // BMV080 default I2C address

void setup()
{
    Serial.begin(115200);

    // Wait for serial to become available
    while (!Serial) delay(10);

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

    // Read (and optionaly configure) sensor parameters
    read_configure_parameters();

    // Set the sensor mode to continuous mode
    if(bmv080.setMode(BMV080_MODE_CONTINUOUS) == true)
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
    // Attempt to read new measurement data from the sensor
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

// Function which reads current configuration state of BMV080 sensor
// and shows you how to set those parameters to custom values
void read_configure_parameters(void)
{
    // Variables to store the parameters, will be used for storing 
    // current values, and (optionaly) setting custom values for each parameter

    float volumetric_mass_density = 0.0f;
    float integration_time = 0.0f;
    uint32_t distribution_id = 0;
    bool do_obstruction_detection = false;
    bool do_vibration_filtering = false;
    uint8_t measurementAlgorithm = E_BMV080_MEASUREMENT_ALGORITHM_BALANCED;

    // ===========================================================
    //          Reading current configuration parameters 
    // ===========================================================

    // Get default parameter "volumetric_mass_density"
    volumetric_mass_density = bmv080.volumetricMassDensity();
    Serial.print("BMV080 'volumetric_mass_density' current value: ");
    Serial.println(volumetric_mass_density);

    // Get default parameter "integration_time"
    integration_time = bmv080.integrationTime();
    Serial.print("BMV080 'integration_time' current value: ");
    Serial.println(integration_time);

    // Get default parameter "distribution_id"
    distribution_id = bmv080.distributionId();
    Serial.print("BMV080 'distribution_id' current value: ");
    Serial.println(distribution_id);

    // Get default parameter "do_obstruction_detection"
    do_obstruction_detection = bmv080.doObstructionDetection();
    Serial.print("BMV080 'do_obstruction_detection' current value: ");
    if(do_obstruction_detection == true)
    {
        Serial.println("true");
    }
    else
    {
        Serial.println("false");
    }

    // Get default parameter "do_vibration_filtering"
    do_vibration_filtering = bmv080.doVibrationFiltering();
    Serial.print("BMV080 'do_vibration_filtering' current value: ");
    if(do_vibration_filtering == true)
    {
        Serial.println("true");
    }
    else
    {
        Serial.println("false");
    }

    // Get default parameter "measurement_algorithm"
    measurementAlgorithm = bmv080.measurementAlgorithm();
    Serial.print("BMV080 'measurement_algorithm' current value: ");
    switch (measurementAlgorithm)
    {
        case E_BMV080_MEASUREMENT_ALGORITHM_FAST_RESPONSE:
            Serial.println("Fast Response");
            break;
        case E_BMV080_MEASUREMENT_ALGORITHM_BALANCED:
            Serial.println("Balanced");
            break;
        case E_BMV080_MEASUREMENT_ALGORITHM_HIGH_PRECISION:
            Serial.println("High Precision");
            break;
        default:
            Serial.println("Unknown");
            break;
    }

    // ===========================================================
    //          Setting new configuration parameters 
    // ===========================================================


    // Uncomment the following lines below to set the parameters to custom values

    /*
    volumetric_mass_density = 1.6f;
    integration_time = 10.0f;
    distribution_id = 3;
    do_obstruction_detection = true;
    do_vibration_filtering = false;
    measurementAlgorithm = E_BMV080_MEASUREMENT_ALGORITHM_BALANCED;

    Serial.println("----- Setting new parameters -----");

    // Set custom parameter "volumetric_mass_density" 
    if(bmv080.setVolumetricMassDensity(volumetric_mass_density) == true)
    {
        Serial.print("BMV080 volumetric_mass_density SET TO: ");
        Serial.println(volumetric_mass_density);
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'volumetric_mass_density'");
    }

    // Set custom parameter "integration_time" 
    if(bmv080.setIntegrationTime(integration_time) == true)
    {
        Serial.print("BMV080 integration_time SET TO: ");
        Serial.println(integration_time);
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'integration_time'");
    }

    // Set custom parameter "distribution_id" 
    if(bmv080.setDistributionId(distribution_id) == true)
    {
        Serial.print("BMV080 distribution_id SET TO: ");
        Serial.println(distribution_id);
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'distribution_id'");
    }

    // Set custom parameter "do_obstruction_detection" 
    if(bmv080.setDoObstructionDetection(do_obstruction_detection) == true)
    {
        Serial.print("BMV080 do_obstruction_detection SET TO: ");
        if(do_obstruction_detection == true)
        {
            Serial.println("true");
        }
        else
        {
            Serial.println("false");
        }
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'do_obstruction_detection'");
    }

    // Set custom parameter "do_vibration_filtering"
    if(bmv080.setDoVibrationFiltering(do_vibration_filtering) == true)
    {
        Serial.print("BMV080 do_vibration_filtering SET TO: ");
        if(do_vibration_filtering == true)
        {
            Serial.println("true");
        }
        else
        {
            Serial.println("false");
        }
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'do_vibration_filtering'");
    }

    // Set custom parameter "measurement_algorithm"
    if (bmv080.setMeasurementAlgorithm(measurementAlgorithm) == true)
    {
        Serial.print("BMV080 measurement_algorithm SET TO: ");
        switch (measurementAlgorithm)
        {
            case E_BMV080_MEASUREMENT_ALGORITHM_FAST_RESPONSE:
                Serial.println("Fast Response");
                break;
            case E_BMV080_MEASUREMENT_ALGORITHM_BALANCED:
                Serial.println("Balanced");
                break;
            case E_BMV080_MEASUREMENT_ALGORITHM_HIGH_PRECISION:
                Serial.println("High Precision");
                break;
            default:
                Serial.println("Unknown");
                break;
        }
    }
    else
    {
        Serial.println("Error setting BMV080 parameter 'measurement_algorithm'");
    }

    Serial.println();
    */
}
