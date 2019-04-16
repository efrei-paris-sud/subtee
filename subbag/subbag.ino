
#include <Arduino.h>
#include "secrets.h"
#include "SPIFFS.h"

/** 
 *  Event management global variables 
 *  @see void subbag::serialEvent(void)
 */
String eventString = "";
bool eventReceived = false;

/* Definition of event numbers */
#define EVENT_TRANSLATE 1

/* Definition of the button input pin */
#define BUTTON_1_PIN 23

/**
 * Setup routine
 */
void setup(void) {
  Serial.begin(115200);
  displaySetup();
  wifiSetup(WIFI_SSID, WIFI_PASS);

  pinMode(BUTTON_1_PIN, INPUT);

  /* Mount FS to read files from the flash memory */
  if(!SPIFFS.begin(true)) {
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }
}

/**
 * Main loop routine
 */
void loop(void) {
  /** Event Received from PC **/
  serialEvent();
  if (eventReceived) {
    processEventReceived();
    
    // clear the string:
    eventString = "";
    eventReceived = false;
  }

  /* Manually trigger translation for the demo */
  if(digitalRead(BUTTON_1_PIN) == HIGH) {
    Serial.println("Button 1 triggered");

    processButton1();

    delay(1000);
  }
}

/**
 * Function for demo purpose, reads a file from fs for Speech-To-Text processing server-side, then translate the text and displays the translation.
 */
void processButton1(void) {
  String rtn = apiMockSpeechToText("/bonjour.ogg");
  rtn = apiTranslate(rtn, "fr", "en");
  displayString(rtn);
}

/**
 * Helper function to get a part of an event (example: 1:test:fr:en)
 *                                 Part numbers:       0   1  2  3          
 */
String getEventValue(String data, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == ':' || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

/**
 * Processes a received event and takes necessary actions
 */
void processEventReceived() { 
  switch(getEventValue(eventString, 0).toInt()) {
    case EVENT_TRANSLATE: {
      String rtn = apiTranslate(getEventValue(eventString, 1), getEventValue(eventString, 2), getEventValue(eventString, 3));
      displayString(rtn);
      Serial.println("Translate event processed");
      break;
    }
    default:
      Serial.println("Unknown event received.");
    break;
  }
}

/**
 * Listens for incoming events on SerialPort.
 * The event is stored in the eventString variable and the flag eventReceived is raised when the event is available for processing.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    eventString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      eventReceived = true;
    }
  }
}
