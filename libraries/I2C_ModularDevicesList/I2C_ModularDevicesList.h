#ifndef I2C_MODULAR_DEVICE_LIST
#define I2C_MODULAR_DEVICE_LIST

#include <Wire.h>
/*
  Wire library uses 7-bit addressing for a total of 128 addresses from 0x00 to 0x7F
  the usable and not reserved range is between 0x08 and 0x77 -> 112 usable addresses
*/
#define USABLE_ADDRESSES_RANGE_LOW 0x08
#define USABLE_ADDRESSES_RANGE_HIGH 0x77
#define TOTAL_AVAILABLE_ADDRESSES USABLE_ADDRESSES_RANGE_HIGH - USABLE_ADDRESSES_RANGE_LOW + 1

enum device_statuses
{
    NOT_FOUND,  // 0
    DISCOVERED, // 1
    INITIALISED // 2
};

class I2C_ModularDevicesList
{
public:
    I2C_ModularDevicesList(); // Constructor
    void scan_I2C_bus();
    int device_status_by_address(uint8_t address);
private:
    int device_status_array[TOTAL_AVAILABLE_ADDRESSES] = {NOT_FOUND}; // occurrence vector
};

#endif /*I2C_MODULAR_DEVICE_LIST*/

// #include <Wire.h>

// /*
//   Wire library uses 7-bit addressing for a total of 128 addresses from 0x00 to 0x7F
//   the usable and not reserved range is between 0x08 and 0x77 -> 112 usable addresses
// */
// #define USABLE_ADDRESSES_RANGE_LOW 0x08
// #define USABLE_ADDRESSES_RANGE_HIGH 0x77
// #define TOTAL_AVAILABLE_ADDRESSES USABLE_ADDRESSES_RANGE_HIGH - USABLE_ADDRESSES_RANGE_LOW + 1

// void scan_I2C_devices(bool* addresses_occurrence_vector) {

//   for (byte address = USABLE_ADDRESSES_RANGE_LOW; address <= USABLE_ADDRESSES_RANGE_HIGH; ++address) {
//     //test for available devices in bus
//     Wire.beginTransmission(address);
//     byte end_of_trasmission_byte = Wire.endTransmission();

//     // switch-case for end of trasmission byte
//     switch (end_of_trasmission_byte) {
//       case 0:
//         Serial.println("Success: Transmission completed successfully.");

//         //on successful transmission we check the acnkowledged device's address on occurrence vector
//         // we offset the value of address to match array length
//         addresses_occurrence_vector[address - USABLE_ADDRESSES_RANGE_LOW] = true;
//         break;

//       // since we will not send data in this scan, we would never trigger this case
//       // case 1:
//       //   Serial.println("Error: Data too long. The data being sent exceeds the buffer size (default 32 bytes on most Arduino boards).");
//       //   break;
//       case 2:
//         Serial.println("Error: No ACK received on address.");
//         break;
//       // as for case 1.
//       // case 3:
//       //   Serial.println("Error: No ACK received on data.");
//       //   break;
//       case 4:
//         Serial.println("Error: Other unspecified error during transmission.");
//         break;
//       default:
//         Serial.println("Unknown error.");
//         break;
//     }
//   }
