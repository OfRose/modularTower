#include <Wire.h>

int led1 = 2;
int led2 = 3;

void setup() {
  Serial.begin(9600);

  Wire.begin(9);                 // join I2C bus with address #9
  Wire.onRequest(requestEvent);  // register event

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);


  digitalWrite(led1, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led1, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(led2, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led2, LOW);   // turn the LED off by making the voltage LOW
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  uint32_t map_len_prova = 0x12ABCDEF;
  byte tmp = 0;
  for (int i = 0; i < 4; i++) {
    // mando da msb a lsb
    tmp = (map_len_prova >> ((3 - i) * 8)) & 0xFF;
    Serial.println(tmp, HEX);
    Wire.write(tmp);
  }
  // respond with message of 6 bytes
  // as expected by master
}
