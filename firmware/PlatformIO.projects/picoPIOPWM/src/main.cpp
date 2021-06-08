#include <Arduino.h>

extern "C" {
void pioPWM();
};

void setup() {
  // put your setup code here, to run once:
  pioPWM();
}

void loop() {
  // put your main code here, to run repeatedly:
  // do nothing
}