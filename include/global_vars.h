/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#define RESIST_UP      1
#define RESIST_DOWN    2
#define RESIST_REAR    4
#define MAX_OPT_RESISTANCE 7

#define RESISTANCE_DEFAULT RESIST_UP + RESIST_DOWN

#define KEY_ENTER   0
#define KEY_CANCEL  1
#define KEY_PLUS    2
#define KEY_MINUS   3
#define DOOR_SENSOR 4

#define STATE_MACHINE_NONE      0
#define STATE_MACHINE_COOKING   1
#define STATE_MACHINE_SETUP     2

byte pin_in[] = {
    PIN_PUSH_00, PIN_PUSH_01, PIN_PUSH_02, PIN_PUSH_03, PIN_OPEN_DOOR
}; 

bool pin_res[] = { // Si queremos activo con high (true) o low (false)
    true, true, true, true, true
};

bool develop_mode = false;

byte current_inputs = 0;
bool input_change = false;

bool is_input_active(byte inputs, byte sensor){
    return ((inputs & (1 << sensor)) != 0);
}

bool temp_change = false;
bool temp_change_primary = false;
bool temp_change_secondary = false;

volatile bool zero_crossing_detected = false;
bool zero_crossing_active = false;
volatile unsigned long zero_crossing_timer = 0;   // TIMER MICROS FOR DIMMER CONTROL

int current_temp = 0;
int current_temp_primary = 0;
int current_temp_secondary = 0;

int raw_primary_sensor = 0;
byte resistances = RESISTANCE_DEFAULT;    

int raw_secondary_sensor = 0;

bool resistance_active = false;

bool rear_fan = false;

byte active_state_machine = STATE_MACHINE_NONE;
byte last_state_machine = STATE_MACHINE_NONE;