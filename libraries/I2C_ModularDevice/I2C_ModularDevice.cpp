#include "I2C_ModularDevice.h"
#include <cstring>

I2C_ModularDevice::I2C_ModularDevice()
{
    device_name = std::string("UNINITIALISED");
    device_type = UNINITIALISED;
}

char *I2C_ModularDevice::getDeviceInfo()
{
    char *res = new char[64];
    strcpy(res, device_name.c_str());
    strcat(res, device_types_strings[device_type].c_str());
    return res;
    // return device_types_strings[device_type];
    // return device_name;
}

void I2C_ModularDevice::setDeviceInfo(char *data)
{
    //device_name.copy(data, 32);
    device_name = std::string(data, 32);
    device_type = OUTPUT_DEVICE;
}
