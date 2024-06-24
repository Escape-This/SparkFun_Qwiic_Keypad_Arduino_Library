/*
  This is a example written for the SparkFun Qwiic Keypad
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15168

  Originally written by Wes Furuya @ SparkFun Electronics, February 5th, 2019
  For the Qwiic Joystick.
  Modified for Keypad by Pete Lewis @ SparkFun Electronics, March 17th, 2019

  The Qwiic Keypad is an I2C controlled ATTiny84-based 12 Button keypad.
  
  Example 3 - Change I2C Address and Read Firmware Version:
  This program uses the Qwiic Keypad Arduino Library to change the I2C address
  for the device. You enter in the DEC value (0-127) of the I2C address
  and wait 1 second. 

  https://github.com/sparkfun/SparkFun_Qwiic_Keypad_Arduino_Library/examples

  Development environment specifics:
  Arduino IDE 1.8.8

  Qwiic KeyPad records any button presses to a stack. It can remember up to 15 buttone presses.
  The master I2C device (for example, an Uno) can ask for the oldest button pressed.
  If the master continues to read in button presses, it will receive the entire stack (from oldest to newest).
  This is handy if you need to go and do something else with your code, you can then come back to the
  keypad and pull in the last 15 button presses.
  
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
*/

#include <Wire.h>
#include "SparkFun_Qwiic_Keypad_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_keypad
KEYPAD keypad1; //Create instance of this object

uint8_t Address = 0x4B; //Start address (Default 0x4B)
byte newAddress[5]; // used to store incoming new address from user via serial terminal

void setup() {
  Serial.begin(9600);
  Serial.println("Qwiic Keypad Example 3 - Change I2C Address");

  if(keypad1.begin(Wire, Address) == false)
  {
    Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
    while(1);
  }
  else
  {
    Serial.print("Address: 0x");
    Serial.print(Address, HEX);
    Serial.print(" Version: ");
    Serial.println(keypad1.getVersion());
  }
}

void loop() {
    //Serial.println("I2C Range: 0-127");
    Serial.println("INPUT- New I2C Address (DEC):");
    Serial.flush(); //Clears buffer
    while (Serial.available() == 0) delay(20); //Waits for entry
    int len = Serial.readBytes(newAddress,5); //Takes entry as a stream of bytes
    
    //Serial.println(len);
    //Serial.println(newAddress[0]);
    //Serial.println(newAddress[1]);
    //Serial.println(newAddress[2]);

    //Converts ASCII char to DEC (Address)
    if (len==1)
    {
    // Serial.println((byte)newAddress[0]-48, HEX);
    Address = (byte)newAddress[0]-48;
    }
    else if (len==2)
    {
    // Serial.println(((byte)newAddress[0]-48)*10+((byte)newAddress[1]-48), HEX);
    Address = ((byte)newAddress[0]-48)*10+((byte)newAddress[1]-48);
    }
    else if (len==3)
    {
    // Serial.println(((byte)newAddress[0]-48)*100+((byte)newAddress[1]-48)*10+((byte)newAddress[2]-48), HEX);
    Address = ((byte)newAddress[0]-48)*100+((byte)newAddress[1]-48)*10+((byte)newAddress[2]-48);
    }

    Serial.print("new address will be: ");
    Serial.println(Address, HEX);
    
    keypad1.setI2CAddress(Address); //Sets new I2C address
      
    //Print out Firmware Version to double check address change
    Serial.print(" Firmware: ");
    Serial.println(keypad1.getVersion());

}