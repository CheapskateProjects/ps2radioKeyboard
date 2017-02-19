/*
  ps2radioKeyboard

  This project converts normal PS/2 keyboard into wireless radio keyboard. 

  Transmitter transmits keyboard presses as characters over radio link ( nRF24L01 ).
  Receiver listens to those radio commands and then inputs them as keyboard emulation calls over the USB. 
  
  created   Feb 2017
  by CheapskateProjects

  ---------------------------
  The MIT License (MIT)

  Copyright (c) 2017 CheapskateProjects

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <PS2Keyboard.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Keyboard data and clock pins
const int DataPin = 7;
const int IRQpin =  3;
// Keyboard to listen
PS2Keyboard keyboard;
// nRF24L01 radio: SPI bus and pins 9, 10 
RF24 radio(9,10);
// Radio addresses
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
  delay(5000);
  
  keyboard.begin(DataPin, IRQpin);
  
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
}

void loop()
{
  if (keyboard.available())
  {
    // read the next key
    char c = keyboard.read();
    // Send that key to listener
    sendKeyPress((int)c);
  }
}

bool sendKeyPress(int incomingChar)
{
    // SEND KEY
    radio.stopListening();
    radio.write(&incomingChar, sizeof(int));
    delay(40);
    radio.startListening();
}
