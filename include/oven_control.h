/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
volatile unsigned long timer_ac_sync = 0;               // TIMER MICROS FOR DIMMER CONTROL
unsigned long timer_counter_00 = millis();              // GLOBAL
unsigned long timer_counter_01 = 0;      // FULL TIMER ACTION COUNTER
unsigned long timer_counter_02 = 0;      // FAST TIMER ACTION COUNTER
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
    unsigned long now = millis();

    // ANTI OVERFLOW (UNSIGNED LONG, 50 DAYS)
    if (timer_counter_00 > now) {
        timer_counter_00 = millis();
        timer_counter_01 = timer_counter_00;
        timer_counter_02 = timer_counter_00;
    }
    else
        timer_counter_00 = now;

    // FAST ACTIONS TIMER
    if (timer_counter_00 >= timer_counter_02){
        FAST_CLICK = true;
        timer_counter_02 = timer_counter_00 + (TIME_CLICK/4);
        if (timer_counter_02 < timer_counter_00) timer_counter_02 = 0xffffffff;
    }
    else {
        FAST_CLICK = false;
    }
    
    // FULL ACTION TIMER
    if (timer_counter_00 >= timer_counter_01){
        FULL_CLICK = true;
        timer_counter_01 = millis() + TIME_CLICK;
        if (timer_counter_01 < timer_counter_00) timer_counter_01 = 0xffffffff;
    }
    else {
        FULL_CLICK = false;
    }
}
