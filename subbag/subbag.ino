
#include <Arduino.h>
#include <WiFi.h>
#include <driver/adc.h>

void setup(void) {
  Serial.begin(9600);
  displaySetup();
  wifiSetup();
}

void loop(void) {
  displayString("hello guys, how are you ? i'm fine and you. What do you think about this shit ?");
}
