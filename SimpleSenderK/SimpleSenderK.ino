/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as SendDemo.
 *
 *  Copyright (C) 2020-2022  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  MIT License
 */
#include <Arduino.h>

#if !defined(ARDUINO_ESP32C3_DEV)
#define DISABLE_CODE_FOR_RECEIVER // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
#endif
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp> // include the library

const int switchPin = 7;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    pinMode(switchPin, INPUT);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

    // The IR library setup. That's all!
    IrSender.begin(); // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin and enable feedback LED at default feedback LED pin
    disableLEDFeedback(); // Disable feedback LED at default feedback LED pin
}

// Sony TV power on command details
const uint8_t sonyAddress = 0x01; // 5-bit address for Sony devices
const uint16_t sonyCommandPowerOn = 0x15; // 7-bit command for power on
const uint8_t sRepeats = 3;

// 0x01 0x12 1 gives volume up 
// 0x01 0x13 1 gives volume up 

// 0x01 0x0 3 gives the number 1
// 0x01 0x1 3 gives the number 2
// 0x01 0x2 3 gives the number 3
// 0x01 0x3 3 gives the number 4
//...
// 0x01 0x10 1 gives the channel up
// 0x01 0x11 1 gives the channel down

// 0x01 0x14 1 gives mute

// 0x01 0x15 toggles on and off

void loop() {

      int buttonState = digitalRead(switchPin);
  
  // If button is pressed send power code command
   if (buttonState == HIGH) {
      Serial.println();
      Serial.print(F("Send Sony command: address=0x"));
      Serial.print(sonyAddress, HEX);
      Serial.print(F(", command=0x"));
      Serial.print(sonyCommandPowerOn, HEX);
      Serial.print(F(", repeats="));
      Serial.print(sRepeats);
      Serial.println();
  
      // Send the Sony power on command
      IrSender.sendSony(sonyAddress, sonyCommandPowerOn, sRepeats);
   }

    // Wait for a while before sending the command again
    delay(100); // 5-second delay
}
