#include <Wire.h>
#include <I2C_ModularDevicesList.h>

I2C_ModularDevicesList deviceList = I2C_ModularDevicesList();

void setup() {
  Wire.begin();

  Serial.begin(9600);
  while (!Serial) {};
}

void loop() {

  deviceList.scan_I2C_bus();
  
  for (byte i = USABLE_ADDRESSES_RANGE_LOW; i <= USABLE_ADDRESSES_RANGE_HIGH; i++) {
    Serial.print(deviceList.device_status_by_address(i));
    Serial.print(" ");
  }
  Serial.print("\n");




  //Serial.println("Richiedo dati a indirizzo ");


  // for (int i = 0; i < device_num; i++) {
  //   Serial.print("Richiedo dati a indirizzo ");
  //   Serial.println(device_addresses[i]);

  //   Wire.requestFrom((int)device_addresses[i], 7);

  //   Serial.println("Leggo dati inviati:");

  //   Serial.print('\t');
  //   while (Wire.available()) {  // slave may send less than requested
  //     char c = Wire.read();     // receive a byte as character
  //     Serial.print(c);          // print the character
  //   }

  //   Serial.println();
  // }
  delay(5000);  // Wait 5 seconds for next scan
}
