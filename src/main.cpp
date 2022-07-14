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
#if defined BOARD_TEST
  #include <board_test.h>
  byte last_input = 0;
#elif defined FORMAT_EEPROM
  //EMPTY
#else // NORMAL MODE
  #include <melodys.h>
  #include <oven_control.h>
#endif

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
  pinMode(PIN_TEMP_SENSOR_01, INPUT);
  pinMode(PIN_TEMP_SENSOR_02, INPUT);
  pinMode(PIN_PUSH_00, INPUT);
  pinMode(PIN_PUSH_01, INPUT);
  pinMode(PIN_PUSH_02, INPUT);
  pinMode(PIN_PUSH_03, INPUT);
  //INTERRUPTIONS:
  //attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), FUNCTION, MODO);

  Serial.begin(BAUDRATE);
  Serial.print ("STARTING openELECTRO for ovenCONTROL\n");
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
      read_temperature_A1();
      read_temperature_A2();
    }

    // FAST CLICK TIMER ACTIONS
    if (FAST_CLICK == true){
      if (control_pcb_fan() != 0) {
        // TODO: Mostrar mensaje segun error...
        Serial.print("¡¡¡ ATENCION: NO SE HA ENCONTRADO SENSOR TEMPERATURA A1 !!! \n");
        start_melody(&ALARM_MELODY);
      };
      
      open_door();
    }
  #endif  
}