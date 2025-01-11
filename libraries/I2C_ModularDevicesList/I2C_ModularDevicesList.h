#ifndef I2C_MODULAR_DEVICE_LIST
#define I2C_MODULAR_DEVICE_LIST

#include <Wire.h>
#include <I2C_ModularDevice.h>
#include <unordered_map>

/*
  Wire library uses 7-bit addressing for a total of 128 addresses from 0x00 to 0x7F
  the usable and not reserved range is between 0x08 and 0x77 -> 112 usable addresses
*/
#define USABLE_ADDRESSES_RANGE_LOW 0x08
#define USABLE_ADDRESSES_RANGE_HIGH 0x77
#define TOTAL_AVAILABLE_ADDRESSES USABLE_ADDRESSES_RANGE_HIGH - USABLE_ADDRESSES_RANGE_LOW + 1
#define MAX_MSG_LEN 7 //WIP

enum device_statuses
{
    NOT_FOUND,                // 0
    DISCOVERED_TO_INITIALISE, // 1
    INSTALLED,                // 2
    ERROR,
};

class I2C_ModularDevicesList
{
public:
    I2C_ModularDevicesList(); // Constructor
    int scan_I2C_bus();
    int device_status_by_address(uint8_t address);
    void init_new_devices();
    I2C_ModularDevice *getDevice(uint8_t address);

private:
    // occurrence and status array
    int device_status_array[TOTAL_AVAILABLE_ADDRESSES] = {NOT_FOUND};

    // hasmap for storing instances of class modularDevice
    std::unordered_map<uint8_t, I2C_ModularDevice *> devices;
};

#endif /*I2C_MODULAR_DEVICE_LIST*/