/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// STATES
#define CALIBRATE_STATE_OFF         0
#define CALIBRATE_STATE_CALIBRATE   1

// EVENTS
#define CALIBRATE_EVENT_KEY_PLUS    0
#define CALIBRATE_EVENT_KEY_MINUS   1
#define CALIBRATE_EVENT_KEY_ENTER   2
#define CALIBRATE_EVENT_KEY_CANCEL  3
#define CALIBRATE_EVENT_TEMP_CHANGE 4
#define CALIBRATE_EVENT_OPEN_DOOR   5

byte calibrate_state = CALIBRATE_STATE_OFF;

byte last_input_calibrate = 0;
byte cur_idx_calibrate = 0;

void set_map_temp(program_eeprom* prog) {
    while((cur_idx_calibrate < TEMP_NUM) && (prog->temp_obj[cur_idx_calibrate] <= current_temp_secondary)){
        prog->temp_map01[cur_idx_calibrate] = raw_primary_sensor;
        Serial.print(String(prog->temp_obj[cur_idx_calibrate]) + ":" + String(prog->temp_map01[cur_idx_calibrate]) + "\n");
        cur_idx_calibrate++;
    }
}

void state_machine_calibrate(byte event){
    switch (calibrate_state) {
        case CALIBRATE_STATE_OFF:
            switch (event) {
                case CALIBRATE_EVENT_KEY_ENTER: 
                    // Empezamos calibracion
                    Serial.print("Start Calibration\n");
                    set_lights(true);
                    start_melody(&OVEN_GO_MELODY);
                    init_program_eeprom(&prog_eeprom_actual); // reseteamos actual
                    // posem fins a temp actual ....

                    cur_idx_calibrate = 0;
                    set_map_temp(&prog_eeprom_actual);
                    set_resistance(resistances, true);

                    calibrate_state = CALIBRATE_STATE_CALIBRATE;
                    break;

                case CALIBRATE_EVENT_KEY_CANCEL:
                    active_state_machine = STATE_MACHINE_COOKING;
                    Serial.print("Cooking mode\n");
                    break;
            }
        break;

        case CALIBRATE_STATE_CALIBRATE:
            switch (event) {
                case CALIBRATE_EVENT_TEMP_CHANGE: 
                    set_map_temp(&prog_eeprom_actual);

                    if(cur_idx_calibrate >= TEMP_NUM){
                        prog_eeprom_actual.mapped01 = true;
                        write_eeprom(); 
                        set_resistance(resistances, false);
                        start_melody(&ON_TEMP_MELODY);
                        set_lights(is_input_active(current_inputs, DOOR_SENSOR));
                        Serial.print("End Calibration\n");
                        calibrate_state = CALIBRATE_STATE_OFF;
                    }                   
                    break;

                case CALIBRATE_EVENT_KEY_CANCEL:
                        read_eeprom(); // Recuperamos ultima config
                        set_resistance(resistances, false);
                        start_melody(&CANCEL_MELODY);
                        set_lights(is_input_active(current_inputs, DOOR_SENSOR));
                        Serial.print("Calibration cancelled\n");
                        calibrate_state = CALIBRATE_STATE_OFF;
                    break;
            }
        break;
     }
}

void inputs_change_calibrate(byte inputs){
    if (is_input_active(inputs, KEY_ENTER) && !is_input_active(last_input_calibrate, KEY_ENTER))
        state_machine_calibrate(CALIBRATE_EVENT_KEY_ENTER);

    if (is_input_active(inputs, KEY_CANCEL) && !is_input_active(last_input_calibrate, KEY_CANCEL))
        state_machine_calibrate(CALIBRATE_EVENT_KEY_CANCEL);

    if (is_input_active(inputs, KEY_PLUS) && !is_input_active(last_input_calibrate, KEY_PLUS))
        state_machine_calibrate(CALIBRATE_EVENT_KEY_PLUS);

    if (is_input_active(inputs, KEY_MINUS) && !is_input_active(last_input_calibrate, KEY_MINUS))
        state_machine_calibrate(CALIBRATE_EVENT_KEY_MINUS);
    
    if (is_input_active(inputs, DOOR_SENSOR) != is_input_active(last_input_calibrate, DOOR_SENSOR))
        state_machine_calibrate(CALIBRATE_EVENT_OPEN_DOOR);

    last_input_calibrate = inputs;
}