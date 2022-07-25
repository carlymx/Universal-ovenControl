/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

float temp_primary_sensor;
float temp_secondary_sensor;

int read_temperature (byte pin, long resistance){
    int temp_sensor = analogRead(pin);    // READ TERMISTOR 
    float res_temp = resistance * (ADC_RATE / (float)temp_sensor); // TENSION TO RESISTENCE 
    float log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor = temp_sensor - 273.15;   // CELSIUS

    return temp_sensor;
}

void read_temperature_primary(){
    if (PRIMARY_SENSOR_DUMMY == true){
        temp_primary_sensor = 20;
        Serial.println("Primary Sensor (DUMMY): " + String(temp_primary_sensor));
    }
    else {
        temp_primary_sensor = read_temperature(PRIMARY_SENSOR, RESISTANCE_PRIMARY_SENSOR); 
        Serial.println("Sensor A1: " + String(temp_primary_sensor));
    }

    current_temp = temp_primary_sensor;
    return;
}

void read_temperature_secundary(){
    if (SECUNDARY_SENSOR_DUMMY == true){
        temp_secondary_sensor = 25;
        Serial.println("Secondary Sensor (DUMMY): " + String(temp_secondary_sensor));
    }
    else {
        temp_secondary_sensor = read_temperature(SECUNDARY_SENSOR, RESISTANCE_SECUNDARY_SENSOR); 
        Serial.println("Sensor A2: " + String(temp_secondary_sensor));
    }
    return;
}
