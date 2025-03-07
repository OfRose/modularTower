#include <I2C_ModularDevicesManager.h>
#include <I2C_ModularDevice.h>

I2C_ModularDevicesManager deviceManager = I2C_ModularDevicesManager();

void setup() {

  Serial.begin(115200);
  while (!Serial) {};
}

void printDevicesStatus() {
  for (byte i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++) {
    if (deviceManager.device_status_by_address(i) != NOT_FOUND) {
      Serial.print(i, HEX);
      Serial.print(" : \t");
      Serial.print("STATUS: ");
      Serial.print(deviceManager.device_status_by_address(i));
      Serial.print("\t");
      // if (deviceManager.device_status_by_address(i) == INSTALLED) {
      //   Serial.print("NAME: ");
      //   Serial.print(deviceManager.getDevice(i)->getDeviceInfo());
      // }
      Serial.print("\n");
    }
  }
}

void loop() {

  int new_devices_num = deviceManager.scan_I2C_bus();
  if (new_devices_num > 0) {
    printDevicesStatus();
    deviceManager.init_new_devices();
    printDevicesStatus();
  }
  uint32_t prova = deviceManager.getDevice(9)->commands_map_len;
  //uint32_t prova = 0x12ABCDEF;
  Serial.println(prova, HEX);

  Serial.write((char*)deviceManager.getDevice(9)->config, deviceManager.getDevice(9)->commands_map_len);
  Serial.println();
  delay(5000);  // Wait 5 seconds for next scan
}
