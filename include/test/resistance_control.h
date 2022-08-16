/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void set_resistance(byte resist, bool active) {
    resistance_active = active;
 
    #ifdef DEBUG_LOG
    Serial.print("Resistances ");
    Serial.print((String)(active ? " ON!: " : "OFF!: "));
    Serial.println(resistances_to_text(resist));
    #endif
}