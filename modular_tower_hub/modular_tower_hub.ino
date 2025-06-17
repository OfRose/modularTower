#include <ModularDeviceController.h>

#include <I_BusManager.h>
#include <I2C_BusManager.h>

#include <I_IOChainingManager.h>

#include <I_Device.h>

I_BusManager* deviceManager = new I2C_BusManager();

ModularDeviceController master = ModularDeviceController(deviceManager, (I_IOChainingManager*)nullptr);

void setup() {

  Serial.begin(115200);
  while (!Serial) {};
}

// void printDevicesStatus() {
//   for (byte i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++) {
//     if (deviceManager.device_status_by_address(i) != NOT_FOUND) {
//       Serial.print(i, HEX);
//       Serial.print(" : \t");
//       Serial.print("STATUS: ");
//       Serial.print(deviceManager.device_status_by_address(i));
//       Serial.print("\t");
//       // if (deviceManager.device_status_by_address(i) == INSTALLED) {
//       //   Serial.print("NAME: ");
//       //   Serial.print(deviceManager.getDevice(i)->getDeviceInfo());
//       // }
//       Serial.print("\n");
//     }
//   }
// }

String prompt = "Select option:\n\t1) Print all devices info;\n\t2) Print all UNIINITIALISED devices info;\n";

void loop() {
  char input;
  Serial.println(prompt);
  while (!Serial.available()) {
  }
  input = Serial.read();
  while (Serial.available()) {
    Serial.read();
  }

  int len;
  I_Device** device_buffer;

  switch (input) {
    case '1':
      master.bus_manager->scan_bus();
      len = master.bus_manager->get_devices_num();
      device_buffer = new I_Device*[len];
      master.bus_manager->get_devices(device_buffer);
      for (int i = 0; i < len; i++) {
        Serial.println(device_buffer[i]->get_info_string().c_str());
      }
      break;
    case '2':
      master.bus_manager->scan_bus();
      len = master.bus_manager->get_UNINITIALISED_devices_num();
      device_buffer = new I_Device*[len];
      master.bus_manager->get_UNINITIALISED_devices(device_buffer);
      for (int i = 0; i < len; i++) {
        Serial.println(device_buffer[i]->get_info_string().c_str());
      }
      break;
    default: Serial.println("Not implemented yet!");
  }

  // int new_devices_num = deviceManager.scan_I2C_bus();
  // if (new_devices_num > 0) {
  //   printDevicesStatus();
  //   deviceManager.init_new_devices();
  //   printDevicesStatus();
  // }
  // uint32_t prova = deviceManager.getDevice(9)->commands_map_len;
  // //uint32_t prova = 0x12ABCDEF;
  // Serial.println(prova, HEX);

  // Serial.write((char*)deviceManager.getDevice(9)->config, deviceManager.getDevice(9)->commands_map_len);
  // Serial.println();
  delay(1000);  // Wait 5 seconds for next scan
}
