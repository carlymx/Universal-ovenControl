/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// LIB INCLUDE
#include <Arduino.h>

#include <configuration.h>
#include <eeprom_conf.h>
#include <global_vars.h>
#include <hardware/inputs_control.h>

#if defined BOARD_TEST
  #include <board_test.h>
  byte last_input = 0;
#elif defined FORMAT_EEPROM
  //EMPTY AT THE MOMENT
#else // NORMAL MODE
  
#endif

#include <hardware/resistance_control.h>
#include <hardware/zero_crossing_control.h>
#include <hardware/dimmer_control.h>
#include <hardware/temperature_control.h>
#include <hardware/fan_control.h>
#include <hardware/light_control.h>
#include <melodys.h>

#include <statemachines/cooking.h>
#include <statemachines/calibrate.h>

#include <oven_control.h>

void setup() {

  // OUTPUTS PINS
  pinMode(PIN_LIGHT_CHAMBER, OUTPUT);
  pinMode(PIN_RESISTOR_UP, OUTPUT);
  pinMode(PIN_RESISTOR_DOWN, OUTPUT);
  pinMode(PIN_RESISTOR_REAR, OUTPUT);
  pinMode(PIN_COOL_FAN, OUTPUT);
  pinMode(PIN_CHAMBER_FAN, OUTPUT);
  pinMode(PIN_PCB_FAN, OUTPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  // INPUTS PINS
  pinMode(PIN_OPEN_DOOR, INPUT);
  pinMode(PRIMARY_SENSOR, INPUT);
  pinMode(SECUNDARY_SENSOR, INPUT);
  pinMode(PIN_PUSH_00, INPUT);
  pinMode(PIN_PUSH_01, INPUT);
  pinMode(PIN_PUSH_02, INPUT);
  pinMode(PIN_PUSH_03, INPUT);
  pinMode(PIN_ZERO_CROSSING, INPUT);
  //INTERRUPTIONS:
  //attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), zero_crossing, RISING);

  Serial.begin(BAUDRATE);
  Serial.print("STARTING Universal ovenCONTROL\n");
  Serial.print("Min Temp: " +String(MIN_TEMP_COOK) +" - Max Temp: " +String(MAX_TEMP_COOK) +"\n");
  delay(2000);
  
  #if defined FORMAT_EEPROM
    format_eeprom();
    read_eeprom();
  #elif defined BOARD_TEST
    board_test_outputs();
  #else
    read_eeprom();
    start_melody(&START_MELODY);
  #endif
}

void loop() {
  #ifdef BOARD_TEST
// TEST MODE:============================
    byte inputs = board_read_inputs();
    board_test_inputs_verif(inputs);
    if (last_input != inputs) {
      Serial.println("Inputs: " + String(inputs));
    }
    last_input = inputs;
//=======================================
  #elif defined FORMAT_EEPROM
    // EMPTY AT THE MOMENT
  #else
// NORMAL MODE:==========================

// CONSTANT TIMER ACTIONS:
  time_click();
  process_sound();
  dimmer_control_fans();

  // Si esta activo y he detectado un zero_crossing, lo paramos
  if((zero_crossing_active == true) && (zero_crossing_detected == true)){
    zero_crossing_timer = micros();
    next_zero = zero_crossing_timer + DIMMER_CONTROL_POWER_100;
    activate_zero_crossing_detect(false);
  }

  // ULTRAFAST TIMER ACTIONS:
  if (ufast_click == true){
      read_inputs();
  }
  // FAST TIMER ACTIONS:
  if (fast_click == true){
      // EMPTY AT THE MOMENT
  }

  // FULL TIMER ACTIONS:
  if (full_click == true){
    activate_zero_crossing_detect(true);  // ENABLE INTERRUPTS
    
    read_temperature_primary();
    read_temperature_secundary();
    
    // Utilizamos ventiladores segun el sensor
    if((active_state_machine == STATE_MACHINE_CALIBRATE) ||
       (prog_eeprom_actual.mapped01 == false)){
      current_temp = current_temp_secondary;
      temp_change = temp_change_secondary;
    }
    else {
      current_temp = current_temp_primary;
      temp_change = temp_change_primary;
    }

    control_pcb_fan(current_temp);
    control_dimmer_rear(current_temp);
    control_dimmer_cool(current_temp);
  }

  // CONSTANT TIMER ACTIONS: State Machine
  switch (active_state_machine) {
      case STATE_MACHINE_COOKING:
        if (input_change == true) inputs_change_cooking(current_inputs);
        if (temp_change == true) state_machine_cooking(COOKING_EVENT_TEMP_CHANGE);
        break;

      case STATE_MACHINE_CALIBRATE:
        if (input_change == true) inputs_change_calibrate(current_inputs);
        if (temp_change == true) state_machine_calibrate(COOKING_EVENT_TEMP_CHANGE);
        break;
  }
  
  input_change = false;
  temp_change = false;
  temp_change_primary = false;
  temp_change_secondary = false;

  //=======================================
    #endif  
}