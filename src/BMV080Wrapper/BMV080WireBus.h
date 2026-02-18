/**
 * @file BMV080WireBus.h
 * @brief Simple I2C bus wrapper for BMV080 using Arduino Wire library
 *
 */

#pragma once

#include <Wire.h>
#include <stddef.h>
#include <stdint.h>

// Error codes for I2C bus operations
typedef enum
{
    wireBusOK = 0,
    wireBusFail = -1
} wireBusError_t;

// Bus type enum
typedef enum
{
    wireBusTypeI2C = 0
} wireBusType_t;

/**
 * @brief Simple I2C bus wrapper class for BMV080 sensor communication
 */
class BMV080WireBus
{
  public:
    /**
     * @brief Initialize the I2C bus with Wire port and address
     * @param wirePort Reference to TwoWire object (e.g., Wire)
     * @param address I2C device address
     */
    void init(TwoWire &wirePort, uint8_t address)
    {
        _wire = &wirePort;
        _address = address;
    }

    /**
     * @brief Set byte order (for compatibility, MSB first is assumed)
     */
    void setByteOrder(uint8_t order)
    {
        // Byte order is handled in read/write methods
        (void)order; // Suppress unused parameter warning
    }

    /**
     * @brief Read 16-bit registers from I2C device
     * @param regAddr Register address (already shifted left by 1 for I2C by the callback)
     * @param data Pointer to buffer to store read data
     * @param length Number of 16-bit words to read
     * @param bytesRead Output parameter for number of bytes actually read
     * @return Error code (0 on success, -1 on failure)
     */
    wireBusError_t readRegister(uint16_t regAddr, uint16_t *data, uint16_t length, size_t &bytesRead)
    {
        if (_wire == nullptr || data == nullptr)
            return wireBusFail;

        bytesRead = 0;

        // Register address is already shifted by callback (word address -> byte address)
        // The shifted value represents the byte address, send as MSB, LSB
        uint8_t regAddrMsb = (uint8_t)((regAddr >> 8) & 0xFF);
        uint8_t regAddrLsb = (uint8_t)(regAddr & 0xFF);

        // Write register address (with stop condition)
        _wire->beginTransmission(_address);
        _wire->write(regAddrMsb);
        _wire->write(regAddrLsb);
        if (_wire->endTransmission() != 0)
            return wireBusFail;

        // Request data (each register is 2 bytes, so length * 2 bytes total)
        uint8_t bytesToRead = length * 2;
        uint8_t bytesReceived = _wire->requestFrom(_address, bytesToRead);

        if (bytesReceived != bytesToRead)
            return wireBusFail;

        // Read data (MSB first, as per BMV080 spec)
        for (uint16_t i = 0; i < length; i++)
        {
            if (_wire->available() < 2)
                return wireBusFail;
            uint8_t msb = _wire->read();
            uint8_t lsb = _wire->read();
            data[i] = (uint16_t)((msb << 8) | lsb);
            bytesRead += 2;
        }

        return wireBusOK;
    }

    /**
     * @brief Write 16-bit registers to I2C device
     * @param regAddr Register address (already shifted left by 1 for I2C by the callback)
     * @param data Pointer to data to write
     * @param length Number of 16-bit words to write
     * @return Error code (0 on success, -1 on failure)
     */
    wireBusError_t writeRegister(uint16_t regAddr, const uint16_t *data, uint16_t length)
    {
        if (_wire == nullptr || data == nullptr)
            return wireBusFail;

        // Register address is already shifted by callback (word address -> byte address)
        // The shifted value represents the byte address, send as MSB, LSB
        uint8_t regAddrMsb = (uint8_t)((regAddr >> 8) & 0xFF);
        uint8_t regAddrLsb = (uint8_t)(regAddr & 0xFF);

        // Start transmission and write register address (MSB first)
        _wire->beginTransmission(_address);
        _wire->write(regAddrMsb);
        _wire->write(regAddrLsb);

        // Write data (MSB first, as per BMV080 spec)
        for (uint16_t i = 0; i < length; i++)
        {
            _wire->write((uint8_t)((data[i] >> 8) & 0xFF)); // MSB
            _wire->write((uint8_t)(data[i] & 0xFF));        // LSB
        }

        uint8_t txError = _wire->endTransmission();
        if (txError != 0)
            return wireBusFail;

        return wireBusOK;
    }

    /**
     * @brief Get bus type (always I2C)
     * @return Bus type (always returns I2C bus type)
     */
    wireBusType_t type() const
    {
        return wireBusTypeI2C;
    }

    /**
     * @brief Ping the I2C device to check if it's connected
     * @return Error code (0 if device responds, -1 on failure)
     */
    wireBusError_t ping()
    {
        if (_wire == nullptr)
            return wireBusFail;

        _wire->beginTransmission(_address);
        uint8_t error = _wire->endTransmission();

        return (error == 0) ? wireBusOK : wireBusFail;
    }

  private:
    TwoWire *_wire = nullptr;
    uint8_t _address = 0;
};
