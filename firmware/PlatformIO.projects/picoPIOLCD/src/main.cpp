#include <Arduino.h>

extern "C" {
void pioLCD();
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  Serial.begin(115200);
  while (!Serial) {;}
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);

  pioLCD(); //rotate logo forever!
}

void loop() {
}