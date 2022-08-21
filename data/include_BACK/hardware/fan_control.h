/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

//==========================================
//                FUNCTIONS                =
//==========================================

byte current_vel_pcb = 0;

void set_fan(unsigned int vel) {
    //dimmer_control(vel);
    if (current_vel_pcb != vel) {
        current_vel_pcb = vel;
        analogWrite(PIN_PCB_FAN, vel);

        #ifdef DEBUG_LOG
        Serial.print("PCB ");
        debuglog_fan(vel);
        #endif
    }
}