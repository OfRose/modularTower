#ifndef I2C_MODULAR_DEVICE_H
#define I2C_MODULAR_DEVICE_H

#include <string>

enum device_types
{
    UNINITIALISED,
    INPUT_DEVICE,
    OUTPUT_DEVICE,
    DEVICE_TYPES_NUM,
};

const std::string device_types_strings[DEVICE_TYPES_NUM] = {"UNINITIALISED", "INPUT_DEVICE", "OUTPUT_DEVICE"};

enum device_commands
{
    INTRODUCTION,
};

class I2C_ModularDevice
{
public:
    I2C_ModularDevice();
    std::string getDeviceInfo();
    void setDeviceInfo(char *data);

private:
    std::string device_name;
    int device_type;
};

#endif // I2C_MODULAR_DEVICE_H
