#include "I2C_ModularDevicesManager.h"

I2C_ModularDevicesManager::I2C_ModularDevicesManager()
{
  Wire.begin();
}

/*
scan indirizzi validi del bus e assegnazione stato DISCOVERED_TO_INITIALISE a new devices
*/

int I2C_ModularDevicesManager::scan_I2C_bus()
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

int I2C_ModularDevicesManager::device_status_by_address(uint8_t address)
{
  return device_status_array[address - USABLE_ADDRESSES_RANGE_LOW];
}

void I2C_ModularDevicesManager::init_new_devices()
{
  for (int i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++)
  {
    if (device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] == DISCOVERED_TO_INITIALISE)
    {
      I2C_ModularDevice *myNewDevice;
      myNewDevice = new I2C_ModularDevice();

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

I2C_ModularDevice *I2C_ModularDevicesManager::getDevice(uint8_t address)
{
  if (device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] == INSTALLED)
  {
    return devices[address];
  }
  return nullptr;
}
