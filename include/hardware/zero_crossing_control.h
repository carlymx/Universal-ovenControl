/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// NORMAL MODE:

unsigned int next_zero = 0;

void zero_crossing() {
    zero_crossing_timer = micros();
    zero_crossing_detected = true;
    next_zero = zero_crossing_timer + DIMMER_CONTROL_POWER_100;
}

void activate_zero_crossing_detect(bool active) {
    if(active == true) {
        zero_crossing_detected = false;
        zero_crossing_active = true;
        interrupts();               // ENABLE INTERRUPTS        
    }
    else {
        zero_crossing_active = false;
        noInterrupts();             // DISABLE INTERRUPTS
    }
}

/*
// https://tinyurl.com/arduino-interrupt
// LOW dispara la interruoción cuando el pin está a nivel bajo.
// CHANGE dispara la interrupción cuando el pin cambia su valor.
// RISING dispara la interrupción cuando el pin pasa de nivel bajo a nivel alto.
// FALLING dispara la interrupción cuando el pin pasa de nivel alto a nivel bajo.
*/
