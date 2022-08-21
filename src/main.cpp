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
  pinMode(SECONDARY_SENSOR, INPUT);
  pinMode(ANALOG_BUTTON1, INPUT);
  pinMode(ANALOG_BUTTON2, INPUT);
  pinMode(ANALOG_BUTTON3, INPUT);
  pinMode(ANALOG_BUTTON4, INPUT);
  pinMode(PIN_ZERO_CROSSING, INPUT);
  //INTERRUPTIONS:
  //attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), zero_crossing, RISING);

  #ifdef USB_SERIAL_PORT
    usb_serial_init();
  #endif

  #ifdef DEBUG_LOG
  Serial.print(RESSTR_STARTING);
  Serial.print(" ");
  Serial.println(RESSTR_APP_NAME);

  Serial.print(RESSTR_MIN_TEMP);
  Serial.print(": ");
  Serial.print(MIN_TEMP_COOK);
  Serial.print(" - ");
  Serial.print(RESSTR_MAX_TEMP);
  Serial.print(": ");
  Serial.println(MAX_TEMP_COOK);
  Serial.print("Voltaje Ref: ");
  Serial.print(VOLTAGE_REF);
  Serial.println("v");
  #endif

  #if defined BOARD_TEST
    board_test_outputs();
  #else
    read_eeprom();
    start_melody(&START_MELODY);
    delay(1000);
  #endif

  //SCREEN INIT:
  screen_init();
  screen_backlight(true);
  screen_write(0, 0, RESSTR_STARTING);
  screen_write(0, 1, RESSTR_APP_NAME);
  delay(2000);
    screen_clear();
    screen_write(0, 1, RESSTR_DEV_VERSION);
    delay(2000);

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
      read_analog_inputs();
      //read_inputs();
  }
  // FAST TIMER ACTIONS:
  if (fast_click == true){
      timers_verify();
      screen_refresh();

      // Si calibramos, miramos en fastclick
      if(active_state_machine == STATE_MACHINE_CALIBRATE){
        read_temperature_primary();
        read_temperature_secondary();

        current_temp = current_temp_secondary;
        temp_change = temp_change_secondary;
      }
  }

  // FULL TIMER ACTIONS:
  if (full_click == true){
    activate_zero_crossing_detect(true);  // ENABLE INTERRUPTS
    
    if(active_state_machine != STATE_MACHINE_CALIBRATE){
      if((prog_eeprom_actual.options & EEPROM_OPT_MAPPED) == 0){
        read_temperature_secondary();
        current_temp = current_temp_secondary;
        temp_change = temp_change_secondary;
      }
      else {
        read_temperature_primary();
        current_temp = current_temp_primary;
        temp_change = temp_change_primary;
      }
    }

    #ifdef DEBUG_LOG
    Serial.print(RESSTR_CURR_TEMP); 
    Serial.print(": ");
    Serial.println(current_temp);
    #endif

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
        if (timer_inactive_timeout == true) state_machine_cooking(COOKING_EVENT_INACTIVE);
        break;

      case STATE_MACHINE_CALIBRATE:
        if (active_state_machine_change == true) activate_setup();
        if (input_change == true) inputs_change_setup(current_inputs);
        if (temp_change == true) state_machine_setup(SETUP_EVENT_TEMP_CHANGE);
        if (timer_inactive_timeout == true) state_machine_setup(SETUP_EVENT_INACTIVE);
        break;
  }
  
  input_change = false;
  temp_change = false;
  temp_change_primary = false;
  temp_change_secondary = false;
  active_state_machine_change = false;
  timer_inactive_timeout = false;

  //=======================================
  #endif  
}