#include "I2C_ModularDevicesList.h"

I2C_ModularDevicesList::I2C_ModularDevicesList() {}

void I2C_ModularDevicesList::scan_I2C_bus()
{
  for (uint8_t address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; ++address)
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
        device_status_array[address - USABLE_ADDRESSES_RANGE_LOW] = DISCOVERED;
      }
      break;

      // since we will not send data in this scan, we would never trigger this case
      // case 1:
      //   Serial.println("Error: Data too long. The data being sent exceeds the buffer size (default 32 bytes on most Arduino boards).");
      //   break;
      // case 2:
      //   Serial.println("Error: No ACK received on address.");
      //   break;
      // as for case 1.
      // case 3:
      //   Serial.println("Error: No ACK received on data.");
      //   break;
      // case 4:
      //   Serial.println("Error: Other unspecified error during transmission.");
      //   break;
      // default:
      //   Serial.println("Unknown error.");
      //   break;
    }
  }

  // int nDevices = 0;
  // Serial.println("Scanning...");
  // for (byte address = 1; address < 127; ++address) {
  //   // The i2c_scanner uses the return value of
  //   // the Wire.endTransmission to see if
  //   // a device did acknowledge to the address.
  //   Wire.beginTransmission(address);
  //   byte error = Wire.endTransmission();

  //   if (error == 0) {

  //     device_addresses[device_num++] = address;

  //     Serial.print("I2C device found at address 0x");
  //     if (address < 16) {
  //       Serial.print("0");
  //     }
  //     Serial.print(address, HEX);
  //     Serial.println("  !");

  //     ++nDevices;
  //   } else if (error == 4) {
  //     Serial.print("Unknown error at address 0x");
  //     if (address < 16) {
  //       Serial.print("0");
  //     }
  //     Serial.println(address, HEX);
  //   }
  // }
  // if (nDevices == 0) {
  //   Serial.println("No I2C devices found\n");
  // } else {
  //   Serial.println("done\n");
  // }
}

int I2C_ModularDevicesList::device_status_by_address(uint8_t address)
{
    return device_status_array[address - USABLE_ADDRESSES_RANGE_LOW];
}