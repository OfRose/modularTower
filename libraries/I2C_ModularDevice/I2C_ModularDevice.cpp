#include "I2C_ModularDevice.h"

I2C_ModularDevice::I2C_ModularDevice()
{
    device_name = "UNINITIALISED";
    device_type = UNINITIALISED;
}

std::string I2C_ModularDevice::getDeviceInfo()
{
    return (device_name + device_types_strings[device_type]);
    // return device_types_strings[device_type];
    // return device_name;
}

void I2C_ModularDevice::setDeviceInfo(char *data)
{
    device_name = data;
    device_type = OUTPUT_DEVICE;
}
