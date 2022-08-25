/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

float get_resistance_therm(int temp_sensor, long resistance, bool pullup){
    if (pullup == true)
        return resistance / (((ADC_RATE - 1) / (float)temp_sensor) - 1);  // TENSION TO RESISTENCE FOR PULLUP
    else
        return resistance * (ADC_RATE - temp_sensor) / (float)temp_sensor; // TENSION TO RESISTENCE FOR PULLDOWN
}

int read_temperature(int temp_sensor, long resistance, float c1, float c2, float c3, bool pullup){
    float res_temp = get_resistance_therm(temp_sensor, resistance, pullup);

    float log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor = temp_sensor - 273.15;   // CELSIUS

    return temp_sensor;
}

int read_temperature_beta(int temp_sensor, long resistance, long therm_r0, int therm_t0, int beta,  bool pullup) {
    float res_temp = get_resistance_therm(temp_sensor, resistance, pullup);

    float steinhart;
    steinhart = res_temp / therm_r0;          // (R/Ro)
    steinhart = log(steinhart);               // ln(R/Ro)
    steinhart /= beta;                        // 1/B * ln(R/Ro)
    steinhart += 1.0 / (therm_t0 + 273.15);   // + (1/To)
    steinhart = 1.0 / steinhart;              // Invert
    steinhart -= 273.15;                      // convert Kelvin to *C 

    temp_sensor = steinhart;
    return temp_sensor;  
}

int temperature_to_raw(int temp, long resistance, long therm_r0, int therm_t0, int beta,  bool pullup) {
    float steinhart = temp;
    steinhart += 273.15; 
    steinhart = 1.0 / steinhart;             
    steinhart -= 1.0 / (therm_t0 + 273.15);
    steinhart *= beta;          
    steinhart = exp(steinhart);
    steinhart *= therm_r0;

    temp = resistance * ADC_RATE / (steinhart + resistance);
    return temp;
}

int read_temperature_map(int raw_temp, program_eeprom* prog) {
    if(((prog->options & EEPROM_OPT_MAPPED) == 0) || (raw_temp == 0))
        return -1;

    if ((prog->options & EEPROM_OPT_DESCENDING) != 0){
        for (unsigned int i=prog->lon_temp - 1; i>=0; i--){
            if (raw_temp < prog->temp_map01[i]) 
                return TEMP_INI + i * TEMP_INTERVAL;
        } 

        return TEMP_INI;
    }
    else {
        for (unsigned int i=0; i<prog->lon_temp; i++){
            if (raw_temp < prog->temp_map01[i]) 
                return TEMP_INI + ((i == 0 ? 0 : i-1) * TEMP_INTERVAL);
        } 

        return TEMP_FIN;
    }
}
