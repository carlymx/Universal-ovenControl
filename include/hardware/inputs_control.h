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

void read_analog_inputs(){
    for(byte i=0; i<sizeof(analog_bottons_list); i++){
        int var_dr = digitalRead(analog_bottons_list[i]);
        if (var_dr >= (ADC_VALUE_B01-DELTA_INPUT) && botton_active == false){
            botton_active = true;
            input_push = 1+i;
            
        }
        else if(var_dr >= (ADC_VALUE_B02-DELTA_INPUT) && botton_active == false){
            botton_active = true;
            input_push = 2+i;
            
        }
        else if(var_dr < (ADC_VALUE_B02-DELTA_INPUT) && botton_active == true){
            botton_active = false;
            input_push = 0;
        }
    }
    if(input_push != 0){
        Serial.println(input_push);
    }
}