/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
// TEST MODE:

void zero_crossing() {
    noInterrupts();             // DISABLE INTERRUPTS
    // timer_ac_sync = micros();
}

void activate_zero_crossing_detect() {
    interrupts();
}

unsigned int current_vel_cool = 0;
unsigned int current_vel_rear = 0;

void set_dimmer_control_cool(unsigned int vel) {
    if (current_vel_cool != vel) {
        current_vel_cool = vel;
        Serial.print("Dimmer Cool: "+String(vel) +" - " +String((vel*100)/(1000000UL/AC_HERTZ)) +"%" +"\n");
    }
}

void set_dimmer_control_rear(unsigned int vel) {
        if (current_vel_rear != vel) {
        current_vel_rear = vel;
        Serial.print("Dimmer Rear: "+String(vel) +" - " +String((vel*100)/(1000000UL/AC_HERTZ)) +"%" +"\n");
    }
}
