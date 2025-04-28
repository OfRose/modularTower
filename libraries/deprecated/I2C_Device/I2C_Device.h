#ifndef I2C_MODULAR_DEVICE_H
#define I2C_MODULAR_DEVICE_H

#include <string>
#include <I_Device.h>
#include <I_BusManager.h>
#include <Wire.h>

enum commands
{
    GET_INFO_STRING_LENGTH,
    GET_INFO_STRING,
};

// const std::string device_types_strings[DEVICE_TYPES_NUM] = {"UNINITIALISED", "INPUT_DEVICE", "OUTPUT_DEVICE"};
/*
enum device_commands
{
    INTRODUCTION,
};
*/

class I2C_Device : public I_Device
{
public:
    I2C_Device(uint8_t address, bool hardware_init = false);
    std::string get_info_string();
    /*
        std::string get_status();
        void load_info_from_board(I_BusManager *bus_manager);
        void requestEvent();
        void receiveEvent(); */

    /*
        char *getDeviceInfo();
        void setDeviceInfo(char *data);
        void loadConfig(uint8_t* commands_map_buffer);
        uint32_t commands_map_len;
        uint8_t config_retrieve_command = 0x01;
        uint8_t* config = nullptr;
     */
private:
    uint8_t address;
    std::string info = "standard";
};

#endif // I2C_MODULAR_DEVICE_H
