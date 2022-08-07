/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#define KEY_ENTER   0
#define KEY_CANCEL  1
#define KEY_PLUS    2
#define KEY_MINUS   3
#define DOOR_SENSOR 4

#define STATE_MACHINE_COOKING   0
#define STATE_MACHINE_CALIBRATE 1
#define STATE_MACHINE_TEST      2

byte pin_in[] = {
    PIN_PUSH_00, PIN_PUSH_01, PIN_PUSH_02, PIN_PUSH_03, PIN_OPEN_DOOR
}; 

bool pin_res[] = { // Si queremos activo con high (true) o low (false)
    true, true, true, true, true
};

byte current_inputs = 0;

bool is_input_active(byte inputs, byte sensor){
    return ((inputs & (1 << sensor)) != 0);
}

bool temp_change = false;
bool temp_change_primary = false;
bool temp_change_secondary = false;
bool input_change = false;

volatile bool zero_crossing_detected = false;
bool zero_crossing_active = false;
volatile unsigned long zero_crossing_timer = 0;   // TIMER MICROS FOR DIMMER CONTROL

byte current_temp = 0;
byte current_temp_primary = 0;
byte current_temp_secondary = 0;

float temp_primary_sensor;
float temp_secondary_sensor;
int raw_primary_sensor = 0;
int raw_secondary_sensor = 0;

byte active_state_machine = STATE_MACHINE_COOKING;
bool active_state_machine_change =  false;

bool rear_fan = false;