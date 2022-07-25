/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
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

#define DEFAULT_TEMP 180
#define MIN_TEMP      30
#define MAX_TEMP     250
#define STEP_TEMP      5

#define RESIST_UP      1
#define RESIST_DOWN    2
#define RESIST_BOTH    3

byte programed_temp = DEFAULT_TEMP;
byte cooking_state = COOKING_STATE_OFF;
byte resistances = RESIST_BOTH;

byte last_input_cooking = 0;

void programed_temp_change(){
    Serial.write("Prog. temp ");
    Serial.write(programed_temp);
    Serial.write("\n");
}

void state_machine_cooking(byte event){
    switch (cooking_state) {
        case COOKING_STATE_OFF:
            switch (event) {
                case COOKING_EVENT_KEY_ENTER: 
                    if (current_temp < programed_temp){
                        // TODO: Arrancamos resistencias...
                        cooking_state = COOKING_STATE_UNDER_TEMP;
                    }
                    else {
                        cooking_state = COOKING_STATE_ON_TEMP;
                    }
                    start_melody(&START_MELODY);
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
                case COOKING_EVENT_KEY_ENTER: break;
                case COOKING_EVENT_KEY_MINUS: break;
                case COOKING_EVENT_KEY_PLUS: break;
                case COOKING_EVENT_KEY_CANCEL: break;
                case COOKING_EVENT_TEMP_CHANGE: break;
                case COOKING_EVENT_OPEN_DOOR: break;
            }
            break;

        case COOKING_STATE_ON_TEMP:
            switch (event) {
                case COOKING_EVENT_KEY_ENTER: break;
                case COOKING_EVENT_KEY_MINUS: break;
                case COOKING_EVENT_KEY_PLUS: break;
                case COOKING_EVENT_KEY_CANCEL: break;
                case COOKING_EVENT_TEMP_CHANGE: break;
                case COOKING_EVENT_OPEN_DOOR: break;
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