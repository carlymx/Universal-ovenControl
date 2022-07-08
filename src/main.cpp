/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

// LIB INCLUDE
#include <Arduino.h>

// PROGRAM INCLUDE
#include <configuration.h>
#include <configuration_pins.h>
#include <oven_control.h>
#include <pitches_notes.h>
#include <melodys.h>

void setup() {

  // OUTPUTS PINS
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
  pinMode(PIN_PUSH_00, INPUT);
  pinMode(PIN_PUSH_01, INPUT);
  pinMode(PIN_PUSH_02, INPUT);
  pinMode(PIN_PUSH_03, INPUT);
  //INTERRUPTIONS:
  //attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), FUNCTION, MODO);

  Serial.begin(BAUDRATE);
  Serial.print ("STARTING openELECTRO\n ovenCONTROL");
  delay (500);
  start_melody(&START_MELODY);
}

void loop() {
// CONSTANT TIMER ACTIONS
  time_click();
  process_sound();

  // FULL CLICK TIMER ACTIONS
  if (FULL_CLICK == true){
    read_temperature_A1();
    read_temperature_A2();
  }

  // FAST CLICK TIMER ACTIONS
  if (FAST_CLICK == true){
    control_pcb_fan();
    open_door();
  }  
}