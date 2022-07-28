/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void set_lights(bool active) {
    if (active == true) digitalWrite(PIN_LIGHT_CHAMBER, HIGH);
    else digitalWrite(PIN_LIGHT_CHAMBER, LOW);

    Serial.print((String)(active ? "PUERTA ABIERTA \n" : "PUERTA CERRADA \n")); 
}