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

byte pin_in[] = {
    PIN_OPEN_DOOR, PIN_PUSH_00, PIN_PUSH_01,
    PIN_PUSH_02, PIN_PUSH_03, PRIMARY_SENSOR,
    SECUNDARY_SENSOR    
}; 


void board_test_outputs(){
    for (byte x=0; x<sizeof(pin_out); x++){
        tone(PIN_SPEAKER, 2000, 500);
        delay (250);
        bool state = false;
        for (byte i=0; i<6; i++){
            digitalWrite(pin_out[x], state=!state);
            delay(2000);
        }
    }
}

byte board_read_inputs(){
    byte res = 0;
    for (byte x=0; x<sizeof(pin_in); x++){
        if ((bool)digitalRead(pin_in[x]) == true) 
            res = res | (1 << x);               
    }
    return res;
}

void board_test_inputs_verif(int inputs){
    noTone(PIN_SPEAKER);
    if (inputs != 0){
        unsigned int var_tone = 200*(inputs);
        tone(PIN_SPEAKER, var_tone);
    }
}
