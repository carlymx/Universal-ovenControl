/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void sm_change_temp() {
    screen_current_temp(current_temp);

    if(develop_mode == true) {
        char aux[14];
        sprintf(aux, "%4d %4d:%3d", raw_primary_sensor, raw_secondary_sensor, current_temp_secondary);
        screen_text(aux);
    }
}

void incr_resistances(){
    resistances++;
    if (resistances > MAX_OPT_RESISTANCE) resistances = 1;
    rear_fan = ((resistances & RESIST_REAR) != 0);  
    screen_resistances(resistances);
}


