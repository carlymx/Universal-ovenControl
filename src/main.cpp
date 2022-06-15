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
#include <oven_control.h>

void setup() {

  // OUTPUTS PINS
  pinMode(PIN_LED_INDICATOR, OUTPUT);
  pinMode(PIN_LIGHT_CHAMBER, OUTPUT);
  pinMode(PIN_RESISTOR_UP, OUTPUT);
  pinMode(PIN_RESISTOR_DOWN, OUTPUT);
  pinMode(PIN_RESISTOR_REAR, OUTPUT);
  pinMode(PIN_COOL_FAN, OUTPUT);
  pinMode(PIN_CHAMBER_FAN, OUTPUT);
  pinMode(PIN_PCB_FAN, OUTPUT);
  pinMode(PIN_SPEEKER, OUTPUT);
  // INPUTS PINS
  pinMode(PIN_OPEN_DOOR, INPUT);
  pinMode(PIN_TEMP_SENSOR_01, INPUT);
  pinMode(PIN_TEMP_SENSOR_02, INPUT);

  Serial.begin(BAUDRATE);
  Serial.print ("STARTING openELECTRO \n");
  delay (500);
}

void loop() {
  time_space();
  
  // FULL ACTIONS
  if (FULL_CLICK == true){
    read_temperature_A1();
    read_temperature_A2();
  }

  //FAST ACTIONS
  if (FAST_CLICK == true){
    control_coler_fan();
  }  
}