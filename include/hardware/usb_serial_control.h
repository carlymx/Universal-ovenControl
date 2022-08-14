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