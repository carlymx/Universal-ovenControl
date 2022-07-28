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

void zero_crossing() {
    noInterrupts();             // DISABLE INTERRUPTS
    timer_ac_sync = micros();
}

void activate_zero_crossing_detect() {
    interrupts();
}

byte current_vel = 0;

void set_fan(byte vel) {
    //dimmer_control(vel);
    if (current_vel != vel) {
        current_vel = vel;
        Serial.print("Fan: "+String(vel) +" - " +String((vel*100)/255) +"%" +"\n");
    }
}