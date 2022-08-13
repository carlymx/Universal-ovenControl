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
    Serial.print("STARTING Universal ovenCONTROL\n");
    Serial.print("Min Temp: " +String(MIN_TEMP_COOK) +" - Max Temp: " +String(MAX_TEMP_COOK) +"\n");
}    

void serial_text(String msg){

}

void serial_resistances(byte resist){

}

void serial_current_temp(int temp){

}

void serial_prog_temp(int temp){

}