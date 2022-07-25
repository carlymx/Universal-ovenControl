/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

int temp_oven [] = {
    COOL_FAN_TEMPERATURE_100, COOL_FAN_TEMPERATURE_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50, 
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

unsigned int power_fan [] = {
    PWM_CONTROL_POWER_100, PWM_CONTROL_POWER_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50,
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

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

void set_fan(byte vel) {
    //dimmer_control(vel);
    Serial.print("Fan: "+String(vel)+"\n");
}

byte control_pcb_fan(float temp) {
    byte err = 0;

    if (temp == 0){ // Byte no puede ser menor
        set_fan(PWM_CONTROL_POWER_100);
        err = 1;
    }
    else {
        for (unsigned int i=0; i<sizeof(temp_oven); i++){
            if (temp >= temp_oven[i]){
                set_fan(power_fan[i]);
                break;
            }
        }            
    }
    return err;
}