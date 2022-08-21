/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
unsigned long timer_counter = millis();              // GLOBAL
unsigned long last_timer = 0;              // GLOBAL
byte fast_counter = 0;      // COUNTER FOR FAST_CLICK ACTIONS
byte full_counter = 0;      // COUNTER FOR FULL_CLICK ACTIONS
bool ufast_click = false;   // ULTRA FAST TIME_CLICK ACTIONS (100ms)
bool fast_click = false;    // FAST TIME_CLICK ACTIONS (100ms x 10)
bool full_click = false;    // FULL TIME_CLICK ACTIONS (

//==========================================
//            TIMER FUNCTIONS              =
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

//==========================================
//          FAN CONTROL FUNCTIONS          =
//==========================================

byte temp_oven [] = {
    COOL_FAN_TEMPERATURE_100, COOL_FAN_TEMPERATURE_75, COOL_FAN_TEMPERATURE_66,
    COOL_FAN_TEMPERATURE_50, COOL_FAN_TEMPERATURE_33, COOL_FAN_TEMPERATURE_20, 0
};

unsigned int power_fan [] = {   // PWM PCB FAN
    PWM_CONTROL_POWER_100, PWM_CONTROL_POWER_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50,
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

unsigned int dimmer_fan [] = {  // DIMMER FAN
    DIMMER_CONTROL_POWER_100, DIMMER_CONTROL_POWER_75, DIMMER_CONTROL_POWER_66, DIMMER_CONTROL_POWER_50,
    DIMMER_CONTROL_POWER_33, DIMMER_CONTROL_POWER_20, DIMMER_CONTROL_POWER_0
};

byte get_index(int temp) {
    for (unsigned int i=0; i<sizeof(temp_oven); i++){
        if (temp >= temp_oven[i]) return i;
    } 

    return (sizeof(temp_oven) + 1);           
} 

byte control_pcb_fan(int temp) {
    if (temp <= 0){ // Byte no puede ser menor
        set_fan(PWM_CONTROL_POWER_100);
        return 1;
    }
    else set_fan(power_fan[get_index(temp)]);

    return 0;
}

byte control_dimmer_rear(int temp) {
    if (temp <= 0){ // Byte no puede ser menor
        set_dimmer_control_rear(DIMMER_CONTROL_POWER_0);
        return 1;
    }
    else 
        set_dimmer_control_rear(rear_fan ? DIMMER_CONTROL_POWER_100 : DIMMER_CONTROL_POWER_0);    
    return 0;
}

byte control_dimmer_cool(int temp) {
    if (temp <= 0){ // Byte no puede ser menor
        set_dimmer_control_cool(DIMMER_CONTROL_POWER_100);
        return 1;
    }
    else 
        //set_dimmer_control_cool(dimmer_fan[get_index(temp)]);
        set_dimmer_control_cool(temp >= COOL_FAN_TEMPERATURE_20 ? DIMMER_CONTROL_POWER_100 : DIMMER_CONTROL_POWER_0);    
    return 0;
}
