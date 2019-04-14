
/**
* LCD RS pin to digital pin 12
* LCD Enable pin to digital pin 11
* LCD D4 pin to digital pin 5
* LCD D5 pin to digital pin 4
* LCD D6 pin to digital pin 3
* LCD D7 pin to digital pin 2
* LCD R/W pin to ground
* 10K variable resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
*/

// include the library code :
#include <LiquidCrystal.h>


// Initialize the library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String eventString = "";         // a String to hold incoming data
bool eventReceived = false;  // whether the string is complete


void setup() {
  //Serial.begin(9600);
  
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD
  lcd.print("SubBag v0.1");
}


void loop() {
   // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD
  lcd.print("SubBag 0.1");
  // set the cursor to column 0, line 1
  // (line 1 is the second row, since counting begins with 0)
  //lcd.setCursor(0, 1);

  /** Event Received from PC **/
  //if (eventReceived) {
    //lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    //lcd.print(eventString);
    
    // clear the string:
    //eventString = "";
    //eventReceived = false;
  //}

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
