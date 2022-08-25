/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// STATES
#define SETUP_STATE_OFF            0
#define SETUP_STATE_CALIBRATE      1
#define SETUP_STATE_FORMAT_EEPROM  2
#define SETUP_STATE_FAN            3
#define SETUP_STATE_REAR_FAN       4
#define SETUP_STATE_COOL_FAN       5

#define SETUP_STATE_DEV_MODE       7
#define SETUP_STATE_RESET          8
#define SETUP_STATE_VERSION        9

#define SETUP_STATE_OPERATION_END 25

// EVENTS
#define SETUP_EVENT_KEY_PLUS    0
#define SETUP_EVENT_KEY_MINUS   1
#define SETUP_EVENT_KEY_ENTER   2
#define SETUP_EVENT_KEY_CANCEL  3
#define SETUP_EVENT_TEMP_CHANGE 4
#define SETUP_EVENT_OPEN_DOOR   5
#define SETUP_EVENT_INACTIVE    6

void activate_setup();
void state_machine_setup(byte event);
void inputs_change_setup(byte inputs);

// ********************************* TODO: L____ hasta aqui el .h ******************************************

/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
//#include <Arduino.h>
//#include <statemachines/setup.h>

byte sel_menu[] = {
    SETUP_STATE_CALIBRATE, SETUP_STATE_FORMAT_EEPROM, 
    SETUP_STATE_FAN, SETUP_STATE_REAR_FAN,  SETUP_STATE_COOL_FAN,
    SETUP_STATE_DEV_MODE, SETUP_STATE_RESET, SETUP_STATE_VERSION
};

String sel_text[] = {
    RESSTR_SETUP_MENU_CALIBRATE, RESSTR_SETUP_MENU_FORMAT_EEPROM, 
    RESSTR_SETUP_MENU_TEST_FAN, RESSTR_SETUP_MENU_TEST_REAR_FAN, RESSTR_SETUP_MENU_TEST_COOL_FAN,
    RESSTR_SETUP_MENU_DEV_MODE, RESSTR_SETUP_MENU_RESET, RESSTR_SETUP_MENU_VERSION
};

byte menu_opt = 0;

byte setup_state = SETUP_STATE_OFF;

byte last_input_setup = 0;
byte cur_idx_calibrate = 0;

byte idx_vel_fan_test = 0;
bool setup_bool_option;

void (* resetSoftware)(void) = 0;

void setup_show_menu(){
    #ifdef DEBUG_LOG
    Serial.println(sel_text[menu_opt]);
    #endif
    screen_text(sel_text[menu_opt]);
}

void setup_add_menu(int a){
    if(a < 0 && menu_opt == 0) menu_opt = sizeof(sel_menu) - 1;
    else {
        menu_opt += a; 
        if(menu_opt >= sizeof(sel_menu)) menu_opt = 0;
    }

    setup_show_menu();
}

void set_map_temp(program_eeprom* prog) {
    while((cur_idx_calibrate < TEMP_NUM) && (TEMP_INI + (cur_idx_calibrate * TEMP_INTERVAL) <= current_temp_secondary)){
        prog->temp_map01[cur_idx_calibrate] = raw_primary_sensor;
        #ifdef DEBUG_LOG
        Serial.print(TEMP_INI + (cur_idx_calibrate * TEMP_INTERVAL));
        Serial.print(": ");
        Serial.println(prog->temp_map01[cur_idx_calibrate]);
        #endif
        // TODO: Mostrar R:xxxx T:xxx
        cur_idx_calibrate++;
    }
}

void state_machine_setup_set_state(byte state){
    switch(state) {
        case SETUP_STATE_OFF:
            screen_info(RESSTR_SETUP);
            setup_show_menu();
            start_timer_inactive(TIMER_INACTIVE);
            break;

        case SETUP_STATE_OPERATION_END:
            start_timer_inactive(TIMER_INACTIVE);
            break;
    }
    
    setup_state = state;
}

void activate_setup(){
    #ifdef DEBUG_LOG
    Serial.println(RESSTR_SETUP_MODE);
    #endif
    screen_prog_temp(0);
    screen_current_temp(current_temp);
    menu_opt = 0;
    state_machine_setup_set_state(SETUP_STATE_OFF);
}

void state_machine_setup(byte event){
    switch(setup_state) {
        case SETUP_STATE_OFF:
            switch(event) {
                case SETUP_EVENT_KEY_ENTER: 
                    switch(sel_menu[menu_opt]) {
                        case SETUP_STATE_CALIBRATE:
                            // Empezamos calibracion
                            screen_text(RESSTR_CALIBRATION_START);
                            screen_info("");
                            screen_prog_temp(TEMP_FIN);
                            #ifdef DEBUG_LOG
                            Serial.println(RESSTR_CALIBRATION_START);
                            #endif

                            set_lights(true);
                            start_melody(&OVEN_GO_MELODY);
                            init_program_eeprom(&prog_eeprom_actual); // reseteamos actual

                            cur_idx_calibrate = 0;
                            set_map_temp(&prog_eeprom_actual);

                            resistances = RESIST_UP;
                            //resistances = RESIST_UP + RESIST_DOWN;
                            set_resistance(resistances, true);
                            screen_resistances(resistances);

                            start_timer_inactive(0);
                            state_machine_setup_set_state(SETUP_STATE_CALIBRATE);
                            break;

                        case SETUP_STATE_FORMAT_EEPROM:
                            screen_info(RESSTR_FORMAT_START);
                            start_timer_inactive(TIMER_INACTIVE);
                            state_machine_setup_set_state(SETUP_STATE_FORMAT_EEPROM);
                            break;
                    
                        case SETUP_STATE_FAN:
                            idx_vel_fan_test = sizeof(power_fan);
                            start_timer_inactive(0);
                            state_machine_setup_set_state(SETUP_STATE_FAN);
                            break;

                        case SETUP_STATE_REAR_FAN:
                            start_timer_inactive(0);
                            screen_info(RESSTR_DISABLED);
                            state_machine_setup_set_state(SETUP_STATE_REAR_FAN);
                            break;

                        case SETUP_STATE_COOL_FAN:
                            start_timer_inactive(0);
                            screen_info(RESSTR_DISABLED);
                            state_machine_setup_set_state(SETUP_STATE_COOL_FAN);
                            break;

                        case SETUP_STATE_DEV_MODE:
                            setup_bool_option = develop_mode;
                            screen_info(setup_bool_option ? RESSTR_ENABLED : RESSTR_DISABLED);
                            start_timer_inactive(TIMER_INACTIVE);
                            state_machine_setup_set_state(SETUP_STATE_DEV_MODE);
                            break;

                        case SETUP_STATE_RESET:
                            screen_info(RESSTR_FORMAT_START);
                            start_timer_inactive(TIMER_INACTIVE);
                            state_machine_setup_set_state(SETUP_STATE_RESET);
                            break;
                    
                        case SETUP_STATE_VERSION:
                            screen_info(APP_VER);
                            start_timer_inactive(TIMER_INACTIVE);
                            state_machine_setup_set_state(SETUP_STATE_VERSION);
                            break;
                   
                    }
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;

                case SETUP_EVENT_KEY_PLUS:
                    setup_add_menu(+1);
                    start_timer_inactive(TIMER_INACTIVE);
                    break;

                case SETUP_EVENT_KEY_MINUS:
                    setup_add_menu(-1);
                    start_timer_inactive(TIMER_INACTIVE);
                    break;

                case SETUP_EVENT_INACTIVE:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;
            }
        break;

        case SETUP_STATE_CALIBRATE:
            switch(event) {
                case SETUP_EVENT_TEMP_CHANGE: 
                    sm_change_temp();
                    set_map_temp(&prog_eeprom_actual);

                    if(cur_idx_calibrate >= TEMP_NUM){
                        prog_eeprom_actual.options = EEPROM_OPT_MAPPED;
                        if(prog_eeprom_actual.temp_map01[0] > prog_eeprom_actual.temp_map01[TEMP_NUM])
                            prog_eeprom_actual.options += EEPROM_OPT_DESCENDING;

                        write_eeprom(); 
                        #ifdef DEBUG_LOG
                        debuglog_calibration(&prog_eeprom_actual);
                        #endif

                        set_resistance(resistances, false);
                        rear_fan = false;
                        start_melody(&ON_TEMP_MELODY);
                        set_lights(is_input_active(current_inputs, DOOR_SENSOR));
                        #ifdef DEBUG_LOG
                        Serial.println(RESSTR_CALIBRATION_END);
                        #endif
                        screen_text(RESSTR_SETUP_MENU_CALIBRATE);
                        screen_info(RESSTR_CALIBRATION_END);
                        state_machine_setup_set_state(SETUP_STATE_OPERATION_END);
                    }                   
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    read_eeprom(); // Recuperamos ultima config
                    set_resistance(resistances, false);
                    start_melody(&CANCEL_MELODY);
                    set_lights(is_input_active(current_inputs, DOOR_SENSOR));
                    #ifdef DEBUG_LOG
                    Serial.println(RESSTR_OPERATION_CANCELED);
                    #endif
                    screen_text(RESSTR_SETUP_MENU_CALIBRATE);
                    screen_info(RESSTR_OPERATION_CANCELED);
                    state_machine_setup_set_state(SETUP_STATE_OPERATION_END);
                    break;

                case SETUP_EVENT_KEY_ENTER: 
                    incr_resistances();
                    set_resistance(resistances, true);
                    break;

            }
            break;

        case SETUP_STATE_FORMAT_EEPROM:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                    init_program_eeprom(&prog_eeprom_actual); // reseteamos actual
                    format_eeprom();
                    write_eeprom();
                    screen_text(RESSTR_SETUP_MENU_FORMAT_EEPROM);
                    screen_info(RESSTR_FORMAT_EEPROM_END);
                    state_machine_setup_set_state(SETUP_STATE_OPERATION_END);
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;

                case SETUP_EVENT_INACTIVE:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;
            }
            break;

        case SETUP_STATE_FAN:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                    if(idx_vel_fan_test > 0) idx_vel_fan_test--;
                    set_fan(power_fan[idx_vel_fan_test]);
                    break;

                case SETUP_EVENT_KEY_MINUS:
                    if(idx_vel_fan_test < sizeof(power_fan) - 1) idx_vel_fan_test++;
                    set_fan(power_fan[idx_vel_fan_test]);
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    set_fan(PWM_CONTROL_POWER_0);
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;
            }
            break;

        case SETUP_STATE_REAR_FAN:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                    set_dimmer_control_rear(DIMMER_CONTROL_POWER_100);
                    screen_info(RESSTR_ENABLED);
                    break;

                case SETUP_EVENT_KEY_MINUS:
                    set_dimmer_control_rear(DIMMER_CONTROL_POWER_0);
                    screen_info(RESSTR_DISABLED);
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    set_dimmer_control_rear(DIMMER_CONTROL_POWER_0);
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;
            }
            break;

        case SETUP_STATE_COOL_FAN:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                    set_dimmer_control_cool(DIMMER_CONTROL_POWER_100);
                    screen_info(RESSTR_ENABLED);
                    break;

                case SETUP_EVENT_KEY_MINUS:
                    set_dimmer_control_cool(DIMMER_CONTROL_POWER_0);
                    screen_info(RESSTR_DISABLED);
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    set_dimmer_control_cool(DIMMER_CONTROL_POWER_0);
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;
            }
            break;

        case SETUP_STATE_DEV_MODE:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                case SETUP_EVENT_KEY_MINUS:
                    setup_bool_option = !setup_bool_option;
                    screen_info(setup_bool_option ? RESSTR_ENABLED : RESSTR_DISABLED);
                    start_timer_inactive(TIMER_INACTIVE);
                    break;

                case SETUP_EVENT_KEY_ENTER:
                    develop_mode = setup_bool_option;
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;
            }
            break;

        case SETUP_STATE_RESET:
            switch(event) {
                case SETUP_EVENT_KEY_PLUS:
                    resetSoftware();
                    break;

                case SETUP_EVENT_KEY_CANCEL:
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;

                case SETUP_EVENT_INACTIVE:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;
            }
            break;

        case SETUP_STATE_VERSION:
            switch(event) {
                //case SETUP_EVENT_KEY_PLUS:
                //case SETUP_EVENT_KEY_MINUS:
                case SETUP_EVENT_KEY_ENTER:
                case SETUP_EVENT_KEY_CANCEL:
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;

                case SETUP_EVENT_INACTIVE:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;
            }
            break;

        case SETUP_STATE_OPERATION_END:
            switch(event) {
                //case SETUP_EVENT_KEY_PLUS:
                //case SETUP_EVENT_KEY_MINUS:
                case SETUP_EVENT_KEY_ENTER:
                case SETUP_EVENT_KEY_CANCEL:
                    state_machine_setup_set_state(SETUP_STATE_OFF);
                    break;

                case SETUP_EVENT_INACTIVE:
                    active_state_machine = STATE_MACHINE_COOKING;
                    break;
            }
            break;

     }
}

void inputs_change_setup(byte inputs){
    if (is_input_active(inputs, KEY_ENTER) && !is_input_active(last_input_setup, KEY_ENTER))
        state_machine_setup(SETUP_EVENT_KEY_ENTER);

    if (is_input_active(inputs, KEY_CANCEL) && !is_input_active(last_input_setup, KEY_CANCEL))
        state_machine_setup(SETUP_EVENT_KEY_CANCEL);

    if (is_input_active(inputs, KEY_PLUS) && !is_input_active(last_input_setup, KEY_PLUS))
        state_machine_setup(SETUP_EVENT_KEY_PLUS);

    if (is_input_active(inputs, KEY_MINUS) && !is_input_active(last_input_setup, KEY_MINUS))
        state_machine_setup(SETUP_EVENT_KEY_MINUS);
    
    if (is_input_active(inputs, DOOR_SENSOR) != is_input_active(last_input_setup, DOOR_SENSOR))
        state_machine_setup(SETUP_EVENT_OPEN_DOOR);

    last_input_setup = inputs;
}