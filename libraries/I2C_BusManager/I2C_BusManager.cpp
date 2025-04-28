#include "I2C_BusManager.h"
#include <Wire.h> // libreria rduino per comunicazione I2C
#include <I_Device.h>
// #include <I2C_Device.h>

#define USABLE_ADDRESSES_RANGE_LOW 0x08
#define USABLE_ADDRESSES_RANGE_HIGH 0x77
#define TOTAL_AVAILABLE_ADDRESSES USABLE_ADDRESSES_RANGE_HIGH - USABLE_ADDRESSES_RANGE_LOW + 1

I2C_BusManager::I2C_BusManager()
{
  Wire.begin();
}

void I2C_BusManager::scan_bus()
{
  // int newly_found_devices[];

  for (uint8_t address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; address++)
  {
    // test for available devices in bus
    Wire.beginTransmission(address);
    uint8_t end_of_trasmission_byte = Wire.endTransmission();

    // switch-case for end of trasmission byte
    switch (end_of_trasmission_byte)
    {
    case 0:
      //  on successful transmission we update the acnkowledged device's address on status array
      //  we offset the value of address to match array length
      if (this->devices.find(address) == this->devices.end())
      {
        this->devices[address] = new I2C_Device(address);
      }else{
        this->devices[address]->set_status(UNINITIALISED);
      }

      break;
    case 2:
      if (this->devices.find(address) != this->devices.end())
      {
        this->devices[address]->set_status(DISCONNECTED);
      }
      break;
    }
  }
}

/* I_Device *I2C_BusManager::scan_bus_for_new_devices(int *devices_num)
{
  int devices_found = 0;
  int newly_found_devices[];

  for (uint8_t address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; address++)
  {
    // test for available devices in bus
    Wire.beginTransmission(address);
    uint8_t end_of_trasmission_byte = Wire.endTransmission();

    // switch-case for end of trasmission byte
    switch (end_of_trasmission_byte)
    {
    case 0:
      //  on successful transmission we update the acnkowledged device's address on status array
      //  we offset the value of address to match array length
      if (device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] == NOT_FOUND)
      {
        device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = DISCOVERED_TO_INITIALISE;
        devices_found++;
      }
      break;
    case 4:
      device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = NOT_FOUND;
      break;
    }
  }



  return devices_found;
}
 */

/* void I2C_BusManager::scan_bus()
{
  // int devices_found = 0;
  uint8_t end_of_trasmission_byte;

  for (uint8_t address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; address++)
  {
    Wire.beginTransmission(address);
    end_of_trasmission_byte = Wire.endTransmission();

    // switch-case for end of trasmission byte
    switch (end_of_trasmission_byte)
    {
    case 0:
      I2C_device_array[address - USABLE_ADDRESSES_RANGE_LOW] = new I2C_Device(address);
      break;
    default:
      I2C_device_array[address - USABLE_ADDRESSES_RANGE_LOW] = nullptr;
    }
  }
  return;
}
 */
/*
scan indirizzi validi del bus e assegnazione stato DISCOVERED_TO_INITIALISE a new devices
*/

/* std::string I2C_BusManager::get_devices_status_string()
{
  std::string res = "STATUS: ";
  for (uint8_t address = 0; address < TOTAL_AVAILABLE_ADDRESSES; address++)
  {
    if (I2C_device_array[address])
    {
      res = res + I2C_device_array[address]->get_status();
    }
  }
  return res;
} */

/* std::string I2C_BusManager::get_device_info_string(uint8_t device_id)
{
    return I2C_device_array[device_id - USABLE_ADDRESSES_RANGE_LOW]->get_info_string();
}
 */
/* int I2C_BusManager::scan_I2C_bus()
{
  int devices_found = 0;
  for (uint8_t address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; address++)
  {
    // test for available devices in bus
    Wire.beginTransmission(address);
    uint8_t end_of_trasmission_byte = Wire.endTransmission();

    // switch-case for end of trasmission byte
    switch (end_of_trasmission_byte)
    {
    case 0:
      // on successful transmission we update the acnkowledged device's address on status array
      //  we offset the value of address to match array length
      if (device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] == NOT_FOUND)
      {
        device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = DISCOVERED_TO_INITIALISE;
        devices_found++;
      }
      break;
    case 4:
      device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = NOT_FOUND;
      break;
    }
  }
  return devices_found;
}

int I2C_BusManager::device_status_by_address(uint8_t address)
{
  return device_status_array[address - USABLE_ADDRESSES_RANGE_LOW];
}

void I2C_BusManager::init_new_devices()
{
  for (int i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++)
  {
    if (device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] == DISCOVERED_TO_INITIALISE)
    {
      I2C_Device *myNewDevice;
      myNewDevice = new I2C_Device();

      uint32_t device_commands_map_len = 0;

      Wire.beginTransmission(i);
      Wire.write(0x00);
      Wire.endTransmission();

      int returned_bytes = Wire.requestFrom(i, MAX_BYTE_TO_REPRESENT_MAP_LEN);

      if (returned_bytes != MAX_BYTE_TO_REPRESENT_MAP_LEN)
      {
        device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] = ERROR;
        return;
      }

      // ricevo da MSB a LSB

      while (Wire.available())
      {
        device_commands_map_len = device_commands_map_len << 8;
        device_commands_map_len = device_commands_map_len | Wire.read();
      }

      myNewDevice->commands_map_len = device_commands_map_len;

      // read_config
      Wire.beginTransmission(i);
      Wire.write(myNewDevice->config_retrieve_command);
      Wire.endTransmission();

      uint8_t commands_map_buffer[device_commands_map_len];

      Wire.requestFrom(i, device_commands_map_len);

      while (!Wire.available()){};

      for (int i = 0; i < device_commands_map_len; i++)
      {
        commands_map_buffer[i] = Wire.read();
      }

      // load_config
      myNewDevice->loadConfig(commands_map_buffer);

      device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] = INSTALLED;
      devices[i] = myNewDevice;
    }
  }
}

I2C_Device *I2C_BusManager::getDevice(uint8_t address)
{
  if (device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] == INSTALLED)
  {
    return devices[address];
  }
  return nullptr;
}
 */