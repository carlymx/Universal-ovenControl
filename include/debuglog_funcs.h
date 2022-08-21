/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void debuglog_resistance(byte resist, bool active) {
    #ifdef DEBUG_LOG
    Serial.print("Resistances ");
    Serial.print(boolean_to_onoff(active));
    Serial.print(": ");
    Serial.println(resistances_to_text(resist));
    #endif
}

void debuglog_light(bool active) {
    #ifdef DEBUG_LOG
    Serial.print("Light: ");
    Serial.println(boolean_to_onoff(active));
    #endif
}

void debuglog_dimmer(unsigned int vel) {
    #ifdef DEBUG_LOG
    Serial.print("Dimmer: ");
    Serial.print(vel);
    Serial.print(" - ");
    Serial.print(vel/(10000/(AC_HERTZ*2)));
    Serial.println("%");
    #endif
}

void debuglog_fan(unsigned int vel) {
    #ifdef DEBUG_LOG
    Serial.print("Fan: ");
    Serial.print(vel);
    Serial.print("/");
    Serial.print((int)PWM_RATE-1);
    Serial.print(" - ");
    Serial.print((int)((vel*100)/(PWM_RATE-1)));
    Serial.println("%");
    #endif
}

void debuglog_temperature(int raw, int temp) {
    #ifdef DEBUG_LOG_HW
    Serial.print("Sensor : "); 
    Serial.print(temp);
    Serial.print(" Raw: ");
    Serial.println(raw);
    #endif
}