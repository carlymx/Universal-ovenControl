/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
volatile unsigned long timer_ac_sync = 0;               // TIMER MICROS FOR DIMMER CONTROL

unsigned long timer_counter = millis();              // GLOBAL
unsigned long last_timer = 0;              // GLOBAL
byte fast_counter = 0;      // COUNTER FOR FAST_CLICK ACTIONS
byte full_counter = 0;      // COUNTER FOR FULL_CLICK ACTIONS
bool ufast_click = false;   // ULTRA FAST TIME_CLICK ACTIONS (100ms)
bool fast_click = false;    // FAST TIME_CLICK ACTIONS (100ms x 10)
bool full_click = false;    // FULL TIME_CLICK ACTIONS (


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
    unsigned long time_now = millis();

    //OVERFLOW
    if (last_timer > time_now){
        timer_counter = time_now;
    }
    last_timer = time_now;

    if (time_now >= timer_counter){
        ufast_click = true;
        fast_counter++;
        full_counter++;
        timer_counter = millis() + TIME_UFAST_CLICK;
        //OVERFLOW:
        if (timer_counter < time_now) timer_counter = 0xFFFFFFFF;
    }
    else ufast_click = false;
    if (fast_counter == TIME_FAST_CLICK){
        fast_counter = 0;
        fast_click = true;
    }
    else fast_click = false;
    if (full_counter == TIME_FULL_CLICK){
        full_counter = 0;
        full_click = true;
    }
    else full_click = false;
}
