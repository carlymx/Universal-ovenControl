/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <includes.h>

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

  #ifdef USB_SERIAL_PORT
    usb_serial_init();
    Serial.println(String(RESSTR_STARTING) + " " + String(RESSTR_APP_NAME));
    Serial.println(String(RESSTR_MIN_TEMP) + ": " + String(MIN_TEMP_COOK) + " - " + String(RESSTR_MAX_TEMP) + ": " + String(MAX_TEMP_COOK));
  #endif

  screen_init();
  screen_backlight(true);
  screen_write(0, 0, String(RESSTR_STARTING) + "...");
  screen_write(0, 1, String(RESSTR_APP_NAME));
  delay(3000);
  
  #if defined FORMAT_EEPROM
    format_eeprom();
    read_eeprom();
  #elif defined BOARD_TEST
    board_test_outputs();
  #else
    read_eeprom();
    start_melody(&START_MELODY);
  #endif

  // Para forzar activacion
  active_state_machine_change = true;
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
      screen_refresh();
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

    Serial.println(String(RESSTR_CURR_TEMP) + ": " + String(current_temp));

    control_pcb_fan(current_temp);
    control_dimmer_rear(current_temp);
    control_dimmer_cool(current_temp);
  }

  // CONSTANT TIMER ACTIONS: State Machine
  switch (active_state_machine) {
      case STATE_MACHINE_COOKING:
        if (active_state_machine_change == true) activate_cooking();
        if (input_change == true) inputs_change_cooking(current_inputs);
        if (temp_change == true) state_machine_cooking(COOKING_EVENT_TEMP_CHANGE);
        break;

      case STATE_MACHINE_CALIBRATE:
        if (active_state_machine_change == true) activate_calibrate();
        if (input_change == true) inputs_change_calibrate(current_inputs);
        if (temp_change == true) state_machine_calibrate(COOKING_EVENT_TEMP_CHANGE);
        break;
  }
  
  input_change = false;
  temp_change = false;
  temp_change_primary = false;
  temp_change_secondary = false;
  active_state_machine_change = false;

  //=======================================
  #endif  
}