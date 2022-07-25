/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

void set_lights(bool active) {
    if (active == true){
        digitalWrite(PIN_LIGHT_CHAMBER, HIGH);
        Serial.print("PUERTA ABIERTA \n");        
    }
    else {
        digitalWrite(PIN_LIGHT_CHAMBER, LOW);
        Serial.print("PUERTA CERRADA \n");        
    }
}