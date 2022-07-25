/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/
volatile unsigned long timer_ac_sync = 0;               // TIMER MICROS FOR DIMMER CONTROL
unsigned long timer_counter_00 = millis();              // GLOBAL
unsigned long timer_counter_01 = timer_counter_00;      // FULL TIMER ACTION COUNTER
unsigned long timer_counter_02 = timer_counter_00;      // FAST TIMER ACTION COUNTER
bool FULL_CLICK = false;    // FULL TIME_CLICK ACTIONS (1/1)
bool FAST_CLICK = false;    // FAST TIME_CLICK ACTIONS (1/4)

//==========================================
//                FUNCTIONS                =
//==========================================

void dimmer_control(bool full) {
    if (full == true){          // ALARM MODE
        noInterrupts();
        digitalWrite(PIN_COOL_FAN, HIGH);
    }
}

void time_click() {
    timer_counter_00 = millis();

    // ANTI OVERFLOW (UNSIGNED LONG, 50 DAYS)
    if (timer_counter_00 < timer_counter_01){
        timer_counter_00 = millis();
        timer_counter_01 = timer_counter_00;
        timer_counter_02 = timer_counter_00;
    }

    // FAST ACTIONS TIMER
    if (timer_counter_00 >= timer_counter_02){
        FAST_CLICK = true;
        timer_counter_02 = millis() + TIME_CLICK/4;
    }
    else {
        FAST_CLICK = false;
    }
    
    // FULL ACTION TIMER
    if (timer_counter_00 > timer_counter_01){
        FULL_CLICK = true;
        timer_counter_01 = millis() + TIME_CLICK;
    }
    else {
        FULL_CLICK = false;
    }
    return;
}