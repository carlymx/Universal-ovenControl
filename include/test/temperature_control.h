/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// DUMMY MODE

float temp_primary_sensor = 20;
float temp_secondary_sensor;

void read_temperature_primary() {
    if (resistance_active == true) temp_primary_sensor += 5;
    else temp_primary_sensor -= 4;

    if (temp_primary_sensor < 20) temp_primary_sensor = 20;

    if (current_temp != temp_primary_sensor){
        current_temp = temp_primary_sensor;
        temp_change = true;
        Serial.println("Primary Sensor (DUMMY): " + String(current_temp));
    }
}
/*
void read_temperature_secundary(){
    temp_secondary_sensor = 25;
}
*/

// NORMAL MODE
int read_temperature (byte pin, long resistance){
    int temp_sensor = analogRead(pin);    // READ TERMISTOR 0-1023 (5v)
    float res_temp = resistance * (ADC_RATE - temp_sensor) / (float)temp_sensor; // TENSION TO RESISTENCE 
    float log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor = temp_sensor - 273.15;   // CELSIUS

    return temp_sensor;
}

void read_temperature_secundary(){
    temp_secondary_sensor = read_temperature(SECUNDARY_SENSOR, RESISTANCE_SECUNDARY_SENSOR); 
    Serial.println("Sensor A2: " + String(temp_secondary_sensor));
}
