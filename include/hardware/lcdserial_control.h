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

#define RESSTR_MONITOR "Mon "

void screen_init(){
}

void screen_backlight(bool active){
    Serial.print(RESSTR_MONITOR);
    Serial.print("Backlight ");
    Serial.println(boolean_to_onoff(active));
}

void screen_clear(){
}

void screen_refresh(){
}

void screen_write(byte x, byte y, String msg){
    Serial.print(RESSTR_MONITOR);
    Serial.println(msg);
}

void screen_text(String msg){
    Serial.print(RESSTR_MONITOR);
    Serial.println(msg);
}

void screen_info(String msg){
    Serial.print(RESSTR_MONITOR);
    Serial.println(msg);
}

void screen_resistances(byte resist){
    Serial.print(RESSTR_MONITOR);
    Serial.print("Resist");
    Serial.print(": ");
    Serial.println(resist);
}

void screen_current_temp(int temp){
    Serial.print(RESSTR_MONITOR);
    Serial.print(RESSTR_CURR_TEMP);
    Serial.print(": ");
    Serial.println(temp);
}

void screen_prog_temp(int temp){
    Serial.print(RESSTR_MONITOR);
    Serial.print(RESSTR_PROG_TEMP);
    Serial.print(": ");
    Serial.println(temp);
}

void screen_alarm(byte alarm){
}