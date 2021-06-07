#include <Arduino.h>

extern "C" {
void pioBlink();
};

void setup() {
  // put your setup code here, to run once:
  pioBlink();
}

void loop() {
  // put your main code here, to run repeatedly:
  // do nothing
}