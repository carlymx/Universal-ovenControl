/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

//==================================//
//           FUNCTIONS:             //
//==================================//

void usb_serial_init(){
    Serial.begin(BAUDRATE);
}    

void serial_print(String msg){
    Serial.print(msg);
}

void serial_println(String msg){
    Serial.println(msg);
}

void serial_input(){
    if (Serial.available()) {
        byte c = Serial.read();
        if(c >= '0' && c < '6'){
            if (c == '0') current_inputs = 0;
            else {
                c -= '1';
                current_inputs = 1 << c;
            }
            input_change = true;
        }
    }
}