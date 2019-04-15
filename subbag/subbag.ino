
#include <Arduino.h>
#include <WiFi.h>
#include <driver/adc.h>

void setup(void) {
  Serial.begin(9600);
  displaySetup();
  //wifiSetup();
}

void loop(void) {
  displayString("Bonjour");
}
