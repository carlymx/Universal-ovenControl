/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// DUMMY MODE

#define DIFF_RAW  6

void read_temperature_primary() { 
    // Siempre leemos el secundario primero
    raw_primary_sensor = raw_secondary_sensor + DIFF_RAW;
    int temp_primary_sensor = read_temperature_map(raw_primary_sensor, &prog_eeprom_actual); // read_temperature(raw_primary_sensor, RESISTANCE_PRIMARY_SENSOR); 

    #ifdef DEBUG_LOG_HW
    Serial.print("A1 DUMMY "); 
    debuglog_temperature(raw_primary_sensor, temp_primary_sensor);
    #endif    

    if (current_temp_primary != temp_primary_sensor){
        current_temp_primary = temp_primary_sensor;
        temp_change_primary = true;
    }
}

void read_temperature_secondary() {
    int temp_secondary_sensor = current_temp_secondary;

    if (resistance_active == true) temp_secondary_sensor += 5;
    else temp_secondary_sensor -= 4;

    if (temp_secondary_sensor < 20) temp_secondary_sensor = 20;

    raw_secondary_sensor = temperature_to_raw(temp_secondary_sensor, RESISTANCE_SECONDARY_SENSOR, THERMISTOR_SECONDARY_RESIST, 
                                              THERMISTOR_SECONDARY_TEMP, THERMISTOR_SECONDARY_BETA, PULLUP_SECONDARY == 1); 

    #ifdef DEBUG_LOG_HW
    Serial.print("A2 DUMMY "); 
    debuglog_temperature(raw_secondary_sensor, temp_secondary_sensor);
    #endif    

    if (current_temp_secondary != temp_secondary_sensor){
        current_temp_secondary = temp_secondary_sensor;
        temp_change_secondary = true;
    }
}