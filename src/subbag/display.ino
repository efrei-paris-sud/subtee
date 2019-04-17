/*
 This file contains all display related code.

 The circuit :
 * LCD RS pin to digital pin 15
 * LCD Enable pin to digital pin 2
 * LCD D4 pin to digital pin 0
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 16
 * LCD D7 pin to digital pin 17
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * V0 is hooked to the ground via a resistor (contrast setting)
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void displaySetup() {
  lcd.begin(16, 2);
}

void displayString(String string) {
  string.trim();
  int i = 0;
  bool firstLoop = true;
  String toShow;

  while(true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    toShow = string.substring(i, i+16);
    if(toShow == "") {
      break;
    }
    lcd.print(toShow);
    i = i + 2;

    /* let some time for the reader to read */
    if(firstLoop) {
      delay(1000);
      firstLoop = false;
    } else {
      delay(450);
    }
  }
}

void __old_displayString(String string) {
  string.trim();
  String part = string.substring(0, 33);
  String top, bottom;
  int to = 33;
  while(part != "") {
    lcd.clear();
    top = part.substring(0, 16);
    bottom = part.substring(16, 33);
    lcd.setCursor(0, 0);
    lcd.print(top);
    lcd.setCursor(0, 1);
    lcd.print(bottom);
    
    part = string.substring(to, to + 32);
    to = to + 32;
    delay(3000);
  }
}
