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
    timer_ac_sync = micros();
    Serial.print("ZeroCrossing: " +String(timer_ac_sync));
}

void activate_zero_crossing_detect() {
    interrupts();               // ENABLE INTERRUPTS
    Serial.print("ZeroCrossing Detection: ON\n");
}

unsigned int current_vel_cool = 0;
unsigned int current_vel_rear = 0;

void dimmer_control_power(byte pin, byte vel){
    // ToDo: Control por micro segundos de los ventiladores
return;
}

void set_dimmer_control_cool(unsigned int vel) {
    if (current_vel_cool != vel) {
        current_vel_cool = vel;
        dimmer_control_power(PIN_COOL_FAN, current_vel_cool);
        Serial.print("Dimmer Cool: "+String(vel) +" - " +String((vel*100)/(1000000UL/AC_HERTZ)) +"%" +"\n");
    }
}

void set_dimmer_control_rear(unsigned int vel) {
        if (current_vel_rear != vel) {
        current_vel_rear = vel;
        dimmer_control_power(PIN_COOL_FAN, current_vel_cool);
        Serial.print("Dimmer Rear: "+String(vel) +" - " +String((vel*100)/(1000000UL/AC_HERTZ)) +"%" +"\n");
    }
}




/*
#define PIN_COOL_FAN        10      // 50/60Hz AC DIMMER CONTROL
#define PIN_CHAMBER_FAN     9       // 50/60Hz AC DIMMER CONTROL

//CONTROL % DIMMER CONFIGURATION: (in microseg)
#define DIMMER_CONTROL_POWER_0     (unsigned int)(((1000000UL/AC_HERTZ)*  0)/200)
#define DIMMER_CONTROL_POWER_20    (unsigned int)(((1000000UL/AC_HERTZ)* 20)/200)
#define DIMMER_CONTROL_POWER_33    (unsigned int)(((1000000UL/AC_HERTZ)* 33)/200)
#define DIMMER_CONTROL_POWER_50    (unsigned int)(((1000000UL/AC_HERTZ)* 50)/200)
#define DIMMER_CONTROL_POWER_66    (unsigned int)(((1000000UL/AC_HERTZ)* 66)/200)
#define DIMMER_CONTROL_POWER_75    (unsigned int)(((1000000UL/AC_HERTZ)* 75)/200)
#define DIMMER_CONTROL_POWER_100   (unsigned int)(((1000000UL/AC_HERTZ)*100)/200)*/