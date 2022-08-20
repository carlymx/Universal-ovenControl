/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void read_temperature_primary(){
    raw_primary_sensor = analogRead(PRIMARY_SENSOR);    // READ TERMISTOR 
    //  TODO: Buscar según tabla
    int temp_primary_sensor = read_temperature_map(raw_primary_sensor, &prog_eeprom_actual); // read_temperature(raw_primary_sensor, RESISTANCE_PRIMARY_SENSOR); 

    #ifdef DEBUG_LOG_HW
    Serial.print("Sensor A1: "); 
    Serial.print(temp_primary_sensor);
    Serial.print(" Raw: ");
    Serial.println(raw_primary_sensor);
    #endif  
    
    if (current_temp_primary != temp_primary_sensor){
        current_temp_primary = temp_primary_sensor;
        temp_change_primary = true;
    }
}

void read_temperature_secondary(){
    raw_secondary_sensor = analogRead(SECONDARY_SENSOR);  
    //int temp_secondary_sensor = read_temperature(raw_secondary_sensor, RESISTANCE_SECONDARY_SENSOR, c1, c2, c3, PULLUP_SECONDARY == 1); 
    int temp_secondary_sensor = read_temperature_beta(raw_secondary_sensor, RESISTANCE_SECONDARY_SENSOR, THERMISTOR_SECONDARY_RESIST, 
                                                      THERMISTOR_SECONDARY_TEMP, THERMISTOR_SECONDARY_BETA, PULLUP_SECONDARY == 1); 
    #ifdef DEBUG_LOG_HW
    Serial.print("Sensor A2: "); 
    Serial.print(temp_secondary_sensor);
    Serial.print(" Raw: ");
    Serial.println(raw_secondary_sensor);
    #endif

    if (current_temp_secondary != temp_secondary_sensor){
        current_temp_secondary = temp_secondary_sensor;
        temp_change_secondary = true;
    }
}
