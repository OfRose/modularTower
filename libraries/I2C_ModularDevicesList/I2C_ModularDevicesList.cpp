#include "I2C_ModularDevicesList.h"

I2C_ModularDevicesList::I2C_ModularDevicesList() {}

int I2C_ModularDevicesList::scan_I2C_bus()
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
      }
      devices_found++;
      break;
    case 4:
      device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = NOT_FOUND;
      break;
    }
  }
  return devices_found;
}

int I2C_ModularDevicesList::device_status_by_address(uint8_t address)
{
  return device_status_array[address - USABLE_ADDRESSES_RANGE_LOW];
}

void I2C_ModularDevicesList::init_new_devices()
{
  for (int i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++)
  {
    if (device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] == DISCOVERED_TO_INITIALISE)
    {
      I2C_ModularDevice *myNewDevice;
      myNewDevice = new I2C_ModularDevice();

      char deviceInfoData[MAX_MSG_LEN];
      int c = 0;

      Wire.requestFrom(i, MAX_MSG_LEN);
      while (Wire.available())
      {
        deviceInfoData[c++] = Wire.read();
      }

      myNewDevice->setDeviceInfo(deviceInfoData);

      device_status_array[i - USABLE_ADDRESSES_RANGE_LOW] = INSTALLED;
      devices[i] = myNewDevice;
    }
  }
}

I2C_ModularDevice *I2C_ModularDevicesList::getDevice(uint8_t address)
{
  if (device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] == INSTALLED)
  {
    return devices[address];
  }
  return nullptr;
}
