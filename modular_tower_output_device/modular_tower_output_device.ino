#include <I2C_Device.h>

int led1 = 2;
int led2 = 3;

I2C_Device myself(9, true);

void setup() {
  Serial.begin(9600);

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