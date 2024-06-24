/*
  An I2C based KeyPad
  By: Nathan Seidle
  SparkFun Electronics
  Date: January 21st, 2018

  The MIT License (MIT)
  
  Copyright (c) 2024 SparkFun Electronics
  
  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions: The
  above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
  "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  Distributed as-is; no warranty is given.

  Updated by: Pete Lewis
  SparkFun Electronics
  Date: March 16th, 2019

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14641

  This example prints which button was pressed and when it was presed.

  Qwiic KeyPad records any button presses to a stack. It can remember up to 15 buttone presses.
  The master I2C device (for example, an Uno) can ask for the oldest button pressed.
  If the master continues to read in button presses, it will receive the entire stack (from oldest to newest).
  This is handy if you need to go and do something else with your code, you can then come back to the
  keypad and pull in the last 15 button presses.
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_keypad
KEYPAD keypad1; //Create instance of this object

char button = 0; //Button '0' to '9' and '*' and '#'
unsigned long timeSincePressed = 0; //Number of milliseconds since this button was pressed

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Qwiic KeyPad Example");

  if (keypad1.begin() == false)
  {
    Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }
  Serial.print("Initialized. Firmware Version: ");
  Serial.println(keypad1.getVersion());
  Serial.println("Press a button: * to do a space. # to go to next line.");
}

void loop(void)
{
  keypad1.updateFIFO();  // necessary for keypad to pull button from stack to readable register
  button = keypad1.getButton();
  timeSincePressed = keypad1.getTimeSincePressed();

  if (button == -1)
  {
    Serial.println("No keypad detected");
    delay(1000);
  }
  else if(button == 0)
  {
    Serial.println("No button has been pressed.");
    delay(1000);
  }
  else
  {
    Serial.println("Button '" + String(button) + "' was pressed " + String(timeSincePressed) + " milliseconds ago.");
  }

  //Do something else. Don't call your Keypad a ton otherwise you'll tie up the I2C bus
  delay(25); //25 is good, more is better
}