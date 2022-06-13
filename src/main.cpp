/*  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
*/

#include <Arduino.h>
#include <configuration.h>
#include <forn_control.h>

void setup() {
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.print ("STARTING openELECTRO \n");
  delay (500);
}

void loop() {
  read_temp01();
}