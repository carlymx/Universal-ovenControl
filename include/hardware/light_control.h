/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void set_lights(bool active) {
    digitalWrite(PIN_LIGHT_CHAMBER, active == true ? HIGH : LOW);
    Serial.print("Light: " + (String)(active ? "ON" : "OFF") + "\n"); 
}