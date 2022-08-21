/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

byte board_read_inputs(){
    byte res = 0;
    for (byte x=0; x<sizeof(pin_in); x++){
        if ((bool)digitalRead(pin_in[x]) == pin_res[x]) 
            res = res | (1 << x);               
    }
    return res;
}

void read_inputs() {
    byte new_inputs = board_read_inputs();
     
    if (new_inputs != current_inputs) {
        current_inputs = new_inputs;
        input_change = true;
    }
}