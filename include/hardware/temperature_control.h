/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

int read_temperature (int temp_sensor, long resistance){
    float res_temp = resistance * (ADC_RATE - temp_sensor) / (float)temp_sensor; // TENSION TO RESISTENCE FOR PULLDOWN
   //float res_temp = resistance / (((ADC_RATE - 1) / (float)temp_sensor) - 1);  // TENSION TO RESISTENCE FOR PULLUP
    float log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor = temp_sensor - 273.15;   // CELSIUS

    return temp_sensor;
}

int read_temperature_map(int raw_temp, program_eeprom* prog) {
    for (unsigned int i=0; i<prog->lon_temp; i++){
        if (raw_temp <= prog->temp_map01[i]) 
            return TEMP_INI + ((i == 0 ? 0 : i-1) * TEMP_INTERVAL);
    } 

    return TEMP_FIN;
}

void read_temperature_primary(){
    raw_primary_sensor = analogRead(PRIMARY_SENSOR);    // READ TERMISTOR 
    //  TODO: Buscar según tabla
    int temp_primary_sensor = read_temperature_map(raw_primary_sensor, &prog_eeprom_actual); // read_temperature(raw_primary_sensor, RESISTANCE_PRIMARY_SENSOR); 

    #ifdef DEBUG_LOG
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

void read_temperature_secundary(){
    raw_secondary_sensor = analogRead(SECUNDARY_SENSOR);  
    int temp_secondary_sensor = read_temperature(raw_secondary_sensor, RESISTANCE_SECUNDARY_SENSOR); 

    #ifdef DEBUG_LOG
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
