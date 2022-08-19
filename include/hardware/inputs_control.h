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


//----------- GLOBAL INPUTS VARIBLES: ---------
byte bottons_array[4] = {ANALOG_BUTTON1, ANALOG_BUTTON2, ANALOG_BUTTON3, ANALOG_BUTTON4};
//int adc_values_array[8] = {1024, 512, 1024, 512, 1024, 512, 1024, 512};
float adc_values_array[] = {0,0,0,0,0,0,0,0};
int _analog_inputs_raw = 0;
byte botton_active = 0;


// FOR TESTING: 
void serial_text(byte push_botton){
    Serial.println("Analog " +String(ANALOG_BUTTON1) +" Raw: " +String(_analog_inputs_raw) +" Botton: " +String(push_botton));
}

void read_analog_inputs(){
    /*for(byte i=0; i<sizeof(bottons_array); i++){
        analog_inputs_raw = analogRead(bottons_array[i]);
    if(_analog_inputs_raw > adc_values_array[i*2]-DELTA_INPUT && botton_active == 0){
        botton_active = 1;
        serial_text(1);}
    else if(_analog_raw > (ADC_RATE/2)-DELTA_INPUT && _analog_raw < (ADC_RATE/2)+DELTA_INPUT && botton_active == 0){
        botton_active = 2;
        serial_text(2);}
    else if(_analog_raw < adc_values_array[i*2]-DELTA_INPUT && botton_active != 0) botton_active = 0;
  }*/
}