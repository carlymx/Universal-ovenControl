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
    debuglog_resistance(resist, active);
    #endif
}