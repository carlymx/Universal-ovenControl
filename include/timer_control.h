/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

unsigned int timer_inactive = 0;
bool timer_inactive_timeout = false;

void timers_verify(){
    timer_inactive_timeout = (timer_inactive > 0) && (timer_inactive < millis());

    if(timer_inactive_timeout == true) timer_inactive = 0;
}

void start_timer_inactive(unsigned int ms){
    timer_inactive = ms == 0 ? 0 : ms + millis();
}