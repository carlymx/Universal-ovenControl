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


byte temp_oven [] = {
    COOL_FAN_TEMPERATURE_100, COOL_FAN_TEMPERATURE_75, COOL_FAN_TEMPERATURE_66,
    COOL_FAN_TEMPERATURE_50, COOL_FAN_TEMPERATURE_33, COOL_FAN_TEMPERATURE_20, 0
};

unsigned int power_fan [] = {
    PWM_CONTROL_POWER_100, PWM_CONTROL_POWER_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50,
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

unsigned int dimmer_fan [] = {
    DIMMER_CONTROL_POWER_100, DIMMER_CONTROL_POWER_75, DIMMER_CONTROL_POWER_66, DIMMER_CONTROL_POWER_50,
    DIMMER_CONTROL_POWER_33, DIMMER_CONTROL_POWER_20, DIMMER_CONTROL_POWER_0
};

//==========================================
//                FUNCTIONS                =
//==========================================

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


byte get_index(float temp) {
    for (unsigned int i=0; i<sizeof(temp_oven); i++){
        if (temp >= temp_oven[i]) return i;
    }            
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
