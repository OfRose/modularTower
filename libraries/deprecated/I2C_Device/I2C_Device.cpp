#include "I2C_Device.h"

I2C_Device::I2C_Device(uint8_t address, bool hardware_init)
{
    this->address = address;
/* 
    if (hardware_init)
    {
        Wire.begin(address);
        Wire.onRequest(this->requestEvent); // register event
        Wire.onReceive(this->receiveEvent);
        info = "info hardware"
    } */
}

std::string I2C_Device::get_info_string()
{
    return info;
}

/* std::string I2C_Device::get_status()
{
    std::string res = std::to_string(address) + "-connected;";
    return res;
}

void I2C_Device::load_info_from_board(I_BusManager *bus_manager)
{
    int bytes_to_read = bus_manager->send_command(address, GET_INFO_STRING_LENGTH);

} */

/* void I2C_Device::requestEvent()
{
    if (code == GET_INFO_STRING_LENGTH)
    {
        uint32_t info_len = info.length();
        uint8_t tmp = 0;
        for (int i = 0; i < 4; i++)
        {
            // mando da msb a lsb
            tmp = (info_len >> ((3 - i) * 8)) & 0xFF;
            Serial.println(tmp, HEX);
            Wire.write(tmp);
        }
    } else if (code == GET_INFO_STRING) {
        Wire.write(info);
      }
} */

/* void I2C_Device::receiveEvent()
{
} */

/*
char *I2C_Device::getDeviceInfo()
{
    char *res = new char[64];
    strcpy(res, device_name.c_str());
    strcat(res, device_types_strings[device_type].c_str());
    return res;
    // return device_types_strings[device_type];
    // return device_name;
}

void I2C_Device::setDeviceInfo(char *data)
{
    //device_name.copy(data, 32);
    device_name = std::string(data, 32);
    device_type = OUTPUT_DEVICE;
}

void I2C_Device::loadConfig(uint8_t* commands_map_buffer)
{
    //std::copy(commands_map_buffer, commands_map_buffer+this->commands_map_len, this->config);
    this->config = new uint8_t[this->commands_map_len];
    std::copy(commands_map_buffer, commands_map_buffer+this->commands_map_len, this->config);
    //this->config = commands_map_buffer;
}
*/

/* void I2C_Device::receiveEvent(int bytesReceived)
{
    while (Wire.available())
    {                            // Check if data is available
        uint8_t c = Wire.read(); // Read a byte
        code = c;
    }
}
 */