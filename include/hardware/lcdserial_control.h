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

void screen_init(){
}

void screen_backlight(bool active){
}

void screen_clear(){
}

void screen_refresh(){
}

void screen_write(byte x, byte y, String msg){
    Serial.println(msg);
}

void screen_text(String msg){
    Serial.println(msg);
}

void screen_resistances(byte resist){
    Serial.println(String(resist));
}

void screen_current_temp(int temp){
    Serial.println(String(RESSTR_CURR_TEMP) + ": " + String(temp));
}

void screen_prog_temp(int temp){
    Serial.println(String(RESSTR_PROG_TEMP) + ": " + String(temp));
}

void screen_alarm(byte alarm){
}