/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void set_lights(bool active) {
    digitalWrite(PIN_LIGHT_CHAMBER, active == true ? HIGH : LOW);
    #ifdef DEBUG_LOG
    Serial.print("Light: ");
    Serial.println((String)(active ? "ON" : "OFF");
    #endif
}