/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

byte current_temp = 0;

#define KEY_ENTER   0
#define KEY_CANCEL  1
#define KEY_PLUS    2
#define KEY_MINUS   3
#define DOOR_SENSOR 4

byte pin_in[] = {
    PIN_PUSH_00, PIN_PUSH_01, PIN_PUSH_02, PIN_PUSH_03, PIN_OPEN_DOOR
}; 

byte current_inputs = 0;

bool is_input_active(byte inputs, byte sensor){
    return ((inputs & (1 << sensor)) != 0);
}

bool temp_change = false;
bool input_change = false;