/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//              BOARD TESTING:              =
//===========================================

byte pin_out[] = {
    PIN_LIGHT_CHAMBER, PIN_RESISTOR_UP, PIN_RESISTOR_DOWN,
    PIN_RESISTOR_REAR, PIN_COOL_FAN, PIN_CHAMBER_FAN, PIN_PCB_FAN
};

byte x = 0;
bool pinIn = false;

byte pin_in[] = {
    PIN_OPEN_DOOR, PIN_PUSH_00, PIN_PUSH_01,
    PIN_PUSH_02, PIN_PUSH_03, PIN_TEMP_SENSOR_01,
    PIN_TEMP_SENSOR_02    
}; 


void board_test_outputs(){
    for (byte x=0; x<sizeof(pin_out); x++){
        tone(PIN_SPEEKER, 2000, 500);
        delay (250);
        bool state = false;
        for (byte i=0; i<20; i++){
            digitalWrite(pin_out[x], state=!state);
            delay(250);
        }
    }
}

void board_test_inputs(){
    noTone(PIN_SPEEKER);
    if (x == sizeof(pin_in)-1){x = 0;} else x++;
    pinIn = (bool)digitalRead(pin_in[x]);
    if (pinIn == true){tone(PIN_SPEEKER, 200*(x+1));}
}