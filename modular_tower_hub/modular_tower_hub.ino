#include <Wire.h>
#include <I2C_ModularDevicesList.h>
#include <I2C_ModularDevice.h>

I2C_ModularDevicesList deviceList = I2C_ModularDevicesList();

void setup() {
  Wire.begin();

  Serial.begin(115200);
  while (!Serial) {};
}

void printDevicesStatus() {
  for (byte i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++) {
    if (deviceList.device_status_by_address(i) != NOT_FOUND) {
      Serial.print(i, HEX);
      Serial.print(" : \t");
      Serial.print("STATUS: ");
      Serial.print(deviceList.device_status_by_address(i));
      Serial.print("\t");
      if (deviceList.device_status_by_address(i) == INSTALLED) {
        Serial.print("NAME: ");
        Serial.print(deviceList.getDevice(i)->getDeviceInfo().c_str());
      }
      Serial.print("\n");
    }
  }
}

void loop() {

  int new_devices_num = deviceList.scan_I2C_bus();
  printDevicesStatus();
  if (new_devices_num > 0) deviceList.init_new_devices();
  printDevicesStatus();

  delay(5000);  // Wait 5 seconds for next scan
}
