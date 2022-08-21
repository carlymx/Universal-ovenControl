/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// DUMMY MODE

void read_temperature_primary() { 
    int temp_primary_sensor = current_temp_primary; 
    if (resistance_active == true) temp_primary_sensor += 5;
    else temp_primary_sensor -= 4;

    if (temp_primary_sensor < 20) temp_primary_sensor = 20;

    // TODO: Usar el raw tambien (o usar solo el raw y obtener de tabla)
    // raw_primary_sensor = xxxxx;

    #ifdef DEBUG_LOG_HW
    Serial.print("A1 DUMMY "); 
    debuglog_temperature(raw_primary_sensor, temp_primary_sensor);
    #endif    

    if (current_temp_primary != temp_primary_sensor){
        current_temp_primary = temp_primary_sensor;
        temp_change_primary = true;
    }
}

void read_temperature_secondary(){
    int temp_secondary_sensor = current_temp_secondary;
    // TODO: Usar el raw tambien
    if (resistance_active == true) temp_secondary_sensor += 5;
    else temp_secondary_sensor -= 4;

    if (temp_secondary_sensor < 20) temp_secondary_sensor = 20;

    // TODO: Usar el raw tambien (o usar solo el raw y obtener de tabla)
    // raw_secondary_sensor = xxxxx;

    #ifdef DEBUG_LOG_HW
    Serial.print("A2 DUMMY "); 
    debuglog_temperature(raw_secondary_sensor, temp_secondary_sensor);
    #endif    

    if (current_temp_secondary != temp_secondary_sensor){
        current_temp_secondary = temp_secondary_sensor;
        temp_change_secondary = true;
    }
}