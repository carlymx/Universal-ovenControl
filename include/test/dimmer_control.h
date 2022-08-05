/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// TEST MODE:

unsigned int current_vel_cool = 0;
unsigned int current_vel_rear = 0;

void dimmer_control_fans(){
}

void set_dimmer_control_cool(unsigned int vel) {
    if (current_vel_cool != vel) {
        current_vel_cool = vel;
        dimmer_control_power(PIN_COOL_FAN, current_vel_cool);
        Serial.print("Dimmer Cool: "+String(vel) +" - " +String(vel/(DIMMER_CONTROL_POWER_100/100)) +"%" +"\n");
    }
}

void set_dimmer_control_rear(unsigned int vel) {
        if (current_vel_rear != vel) {
        current_vel_rear = vel;
        dimmer_control_power(PIN_CHAMBER_FAN, current_vel_rear);
        Serial.print("Dimmer Rear: "+String(vel) +" - " +String(vel/(DIMMER_CONTROL_POWER_100/100)) +"%" +"\n");
    }
}