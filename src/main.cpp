/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

// LIB
#include <Arduino.h>

// PROGRAM
#include <configuration.h>
#include <forn_control.h>

void setup() {
  Serial.begin(BAUDRATE);
  pinMode (PIN_LED_INDICATOR, OUTPUT);
  Serial.print ("STARTING openELECTRO \n");
  delay (500);
}

void loop() {
  time_space();
}