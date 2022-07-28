/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// STATES
#define COOKING_STATE_OFF         0
#define COOKING_STATE_UNDER_TEMP  1
#define COOKING_STATE_ON_TEMP     2

// EVENTS
#define COOKING_EVENT_KEY_PLUS    0
#define COOKING_EVENT_KEY_MINUS   1
#define COOKING_EVENT_KEY_ENTER   2
#define COOKING_EVENT_KEY_CANCEL  3
#define COOKING_EVENT_TEMP_CHANGE 4
#define COOKING_EVENT_OPEN_DOOR   5

#define DEFAULT_TEMP 100
#define MIN_TEMP      30
#define MAX_TEMP     250
#define STEP_TEMP      5

#define DELTA_ON  0
#define DELTA_OFF 5

byte programed_temp = DEFAULT_TEMP;
byte cooking_state = COOKING_STATE_OFF;
byte resistances = RESIST_UP + RESIST_DOWN;

byte last_input_cooking = 0;
bool beep_on_temp = true;

void programed_temp_change(){
    Serial.print("Prog. temp " +String(programed_temp) +" - Max Temp: " +String(MAX_TEMP) +"\n");
}

void verify_temp_under() {
    if (current_temp >= programed_temp + DELTA_ON) {
        set_resistance(resistances, false);
        cooking_state = COOKING_STATE_ON_TEMP;                    
        if (beep_on_temp == true) {
            start_melody(&ON_TEMP_MELODY);
            beep_on_temp = false;
        }
    }
}

void verify_temp_on() {
    if (current_temp <= programed_temp - DELTA_OFF) {
        set_resistance(resistances, true);
        cooking_state = COOKING_STATE_UNDER_TEMP;                    
        if (beep_on_temp == true) {
            start_melody(&ON_TEMP_MELODY);
            beep_on_temp = false;
        }
    }
}

void incr_resistances() {
    resistances++;
    if (resistances > MAX_OPT_RESISTANCE) resistances = 1; 
}

void state_machine_cooking(byte event){
    switch (cooking_state) {
        case COOKING_STATE_OFF:
            switch (event) {
                case COOKING_EVENT_KEY_ENTER: 
                    beep_on_temp = true;
                    if (current_temp < programed_temp){
                        set_resistance(resistances, true);
                        cooking_state = COOKING_STATE_UNDER_TEMP;
                    }
                    else {
                        cooking_state = COOKING_STATE_ON_TEMP;
                    }
                    start_melody(&OVEN_GO_MELODY);
                    break;

                case COOKING_EVENT_KEY_MINUS:
                    programed_temp -= STEP_TEMP; 
                    if (programed_temp < MIN_TEMP) programed_temp = MIN_TEMP;
                    programed_temp_change();
                    break;

                case COOKING_EVENT_KEY_PLUS: 
                    programed_temp += STEP_TEMP; 
                    if (programed_temp > MAX_TEMP) programed_temp = MAX_TEMP;
                    programed_temp_change();
                    break;

                case COOKING_EVENT_KEY_CANCEL: 
                    programed_temp = DEFAULT_TEMP;
                    programed_temp_change();
                    // TODO: Aqui podriamos ir al menu de settings
                    break;

                case COOKING_EVENT_TEMP_CHANGE: break;

                case COOKING_EVENT_OPEN_DOOR: 
                    set_lights(is_input_active(current_inputs, DOOR_SENSOR));                 
                    break;
            }
            break;

        case COOKING_STATE_UNDER_TEMP:
            switch (event) {
                case COOKING_EVENT_KEY_ENTER: 
                    incr_resistances();
                    set_resistance(resistances, true);
                    break;

                case COOKING_EVENT_KEY_MINUS:
                    programed_temp -= STEP_TEMP; 
                    if (programed_temp < MIN_TEMP) programed_temp = MIN_TEMP;
                    programed_temp_change();
                    verify_temp_under();
                    break;

                case COOKING_EVENT_KEY_PLUS: 
                    programed_temp += STEP_TEMP; 
                    if (programed_temp > MAX_TEMP) programed_temp = MAX_TEMP;
                    programed_temp_change();
                    break;

                case COOKING_EVENT_KEY_CANCEL: 
                    set_resistance(resistances, false);
                    start_melody(&CANCEL_MELODY);
                    cooking_state = COOKING_STATE_OFF;
                    break;

                case COOKING_EVENT_TEMP_CHANGE: 
                    verify_temp_under();
                    break;

                case COOKING_EVENT_OPEN_DOOR: 
                    set_lights(is_input_active(current_inputs, DOOR_SENSOR));                 
                    break;
            }
            break;

        case COOKING_STATE_ON_TEMP:
            switch (event) {
                case COOKING_EVENT_KEY_ENTER: 
                    incr_resistances();
                    set_resistance(resistances, false);
                    break;

                case COOKING_EVENT_KEY_MINUS:
                    programed_temp -= STEP_TEMP; 
                    if (programed_temp < MIN_TEMP) programed_temp = MIN_TEMP;
                    programed_temp_change();
                    break;

                case COOKING_EVENT_KEY_PLUS: 
                    programed_temp += STEP_TEMP; 
                    if (programed_temp > MAX_TEMP) programed_temp = MAX_TEMP;
                    programed_temp_change();
                    verify_temp_on();
                    break;

                case COOKING_EVENT_KEY_CANCEL: 
                    set_resistance(resistances, false);
                    start_melody(&CANCEL_MELODY);
                    cooking_state = COOKING_STATE_OFF;
                    break;

                case COOKING_EVENT_TEMP_CHANGE: 
                    verify_temp_on();
                    break;

                case COOKING_EVENT_OPEN_DOOR: 
                    set_lights(is_input_active(current_inputs, DOOR_SENSOR));                 
                    break;
            }
            break;

    }
}

void inputs_change_cooking(byte inputs){
    if (is_input_active(current_inputs, KEY_ENTER) && !is_input_active(last_input_cooking, KEY_ENTER))
        state_machine_cooking(COOKING_EVENT_KEY_ENTER);

    if (is_input_active(current_inputs, KEY_CANCEL) && !is_input_active(last_input_cooking, KEY_CANCEL))
        state_machine_cooking(COOKING_EVENT_KEY_CANCEL);

    if (is_input_active(current_inputs, KEY_PLUS) && !is_input_active(last_input_cooking, KEY_PLUS))
        state_machine_cooking(COOKING_EVENT_KEY_PLUS);

    if (is_input_active(current_inputs, KEY_MINUS) && !is_input_active(last_input_cooking, KEY_MINUS))
        state_machine_cooking(COOKING_EVENT_KEY_MINUS);
    
    if (is_input_active(current_inputs, DOOR_SENSOR) != is_input_active(last_input_cooking, DOOR_SENSOR))
        state_machine_cooking(COOKING_EVENT_OPEN_DOOR);

    last_input_cooking = current_inputs;
}