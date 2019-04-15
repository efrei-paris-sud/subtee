
#include <Arduino.h>

String eventString = "";         // a String to hold incoming data
bool eventReceived = false;  // whether the string is complete

#define EVENT_TRANSLATE 1

void setup(void) {
  Serial.begin(115200);
  displaySetup();
  wifiSetup("iPhone", "azerty75015");

  //displayString("hello world this string is so long omg you know it you are awesome");
}

void loop(void) {
  /** Event Received from PC **/
  serialEvent();
  if (eventReceived) {
    processEventReceived();
    
    // clear the string:
    eventString = "";
    eventReceived = false;
  }

  //displayString("hello");
}


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

void processEventReceived() { 
  switch(getEventValue(eventString, 0).toInt()) {
    case EVENT_TRANSLATE: {
      String rtn = apiTranslate(getEventValue(eventString, 1), "fr", "en");
      displayString(rtn);
      Serial.println("Translate event processed");
      break;
    }
    default:
      Serial.println("Unknown event received.");
    break;
  }
}

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
