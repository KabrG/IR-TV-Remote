/*
 *  Credit to Armin Joachimsmeyer for the SimpleSender examplecode + Library support
 *  Copyright (C) 2020-2022  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
  */
#include <Arduino.h>

#if !defined(ARDUINO_ESP32C3_DEV)
#define DISABLE_CODE_FOR_RECEIVER // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
#endif
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp> // include the library

const int on_pin = 7;
const int volume_up_pin = 8;
const int volume_down_pin = 9;
const int change_tv = 10;

struct command_controls {
  const uint8_t s_address;
  const uint16_t s_command;
  const uint8_t s_repeat;
  
};



void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    
    pinMode(on_pin, INPUT);
    pinMode(volume_up_pin, INPUT);
    pinMode(volume_down_pin, INPUT);
//    pinMode(change_tv, INPUT);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

    IrSender.begin(); // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin and enable feedback LED at default feedback LED pin
    disableLEDFeedback(); // Disable feedback LED at default feedback LED pin

}

// Sony TV power on command details
//const uint8_t sonyAddress = 0x01; // 5-bit address for Sony devices
//const uint16_t sonyCommandPowerOn = 0x15; // 7-bit command for power on
//const uint8_t sRepeats = 3;

// 0x01 0x12 1 gives volume up 
// 0x01 0x13 1 gives volume down 

// 0x01 0x0 3 gives the number 1
// 0x01 0x1 3 gives the number 2
// 0x01 0x2 3 gives the number 3
// 0x01 0x3 3 gives the number 4
//...
// 0x01 0x10 1 gives the channel up
// 0x01 0x11 1 gives the channel down

// 0x01 0x14 1 gives mute

// 0x01 0x15 toggles on and off

void sony_control(void) {
  int on_button = digitalRead(on_pin);
  int volume_up_button = digitalRead(volume_up_pin);
  int volume_down_button = digitalRead(volume_down_pin);

  struct command_controls on = {0x01, 0x15, 3};
  struct command_controls volume_up = {0x01, 0x12, 3};
  struct command_controls volume_down = {0x01, 0x13, 3};

    // If button is pressed send power code command
   if (on_button == HIGH) {
      // Send the Sony power on command
      IrSender.sendSony(on.s_address, on.s_command, on.s_repeat);
      Serial.println("here");
   }
   else if (volume_up_button == HIGH) {
      IrSender.sendSony(volume_up.s_address, volume_up.s_command, volume_up.s_repeat);
   }
   else if (volume_down_button == HIGH) {
      IrSender.sendSony(volume_down.s_address, volume_down.s_command, volume_down.s_repeat);
   }

  
}


void loop() {

    sony_control();
  // If button is pressed send power code command
//   if (on_button == HIGH) {
//      // Send the Sony power on command
//      IrSender.sendSony(sonyAddress, sonyCommandPowerOn, sRepeats);
//   }
//   else if (volume_up_pin == HIGH) {
//    
//   }

    // Wait for a while before sending the command again
    delay(100); // 5-second delay
}


//      Serial.println();
//      Serial.print(F("Send Sony command: address=0x"));
//      Serial.print(sonyAddress, HEX);
//      Serial.print(F(", command=0x"));
//      Serial.print(sonyCommandPowerOn, HEX);
//      Serial.print(F(", repeats="));
//      Serial.print(sRepeats);
//      Serial.println();
