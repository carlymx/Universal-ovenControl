/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

// LIB INCLUDE
#include <Arduino.h>

#include <configuration.h>
#include <eeprom_conf.h>
#include <global_vars.h>
#include <read_inputs.h>

#if defined BOARD_TEST
  #include <board_test.h>
  byte last_input = 0;
#elif defined FORMAT_EEPROM
  //EMPTY
#else // NORMAL MODE
  #include <melodys.h>
  #include <oven_control.h>
#endif

#include <light_control.h>
#include <statemachines/cooking.h>

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
  //INTERRUPTIONS:
  attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), zero_crossing, RISING);

  Serial.begin(BAUDRATE);
  Serial.print ("STARTING openELECTRO for Universal ovenCONTROL\n");
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
    byte inputs = board_read_inputs();
    board_test_inputs_verif(inputs);
    if (last_input != inputs) {
      Serial.println("Inputs: " + String(inputs));
    }
    last_input = inputs;
  #elif defined FORMAT_EEPROM
    // EMPTY
  #else // NORMAL MODE
    // CONSTANT TIMER ACTIONS
    time_click();
    process_sound();

    // FULL CLICK TIMER ACTIONS 
    if (FULL_CLICK == true){
      read_temperature_primary();
      read_temperature_secundary();
      interrupts();             // ENABLE INTERRUPTS
    }

    // FAST CLICK TIMER ACTIONS
    if (FAST_CLICK == true){
      if (control_pcb_fan() != 0) {
        // TODO: Mostrar mensaje segun error...
        Serial.print("¡¡¡ ATENCION: NO SE HA ENCONTRADO SENSOR TEMPERATURA A1 !!! \n");
        start_melody(&ALARM_MELODY);
        dimmer_control(true);
      };
      
      read_inputs();
    }

    // Maquina d'estats
    if (input_change) inputs_change_cooking(current_inputs);
    if (temp_change) state_machine_cooking(COOKING_EVENT_TEMP_CHANGE);
    input_change = false;
    temp_change = false;
    
  #endif  
}