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

    Serial.println("Primary Sensor (DUMMY): " + String(temp_primary_sensor));

    if (current_temp != temp_primary_sensor){
        current_temp = temp_primary_sensor;
        temp_change = true;
    }
}

void read_temperature_secundary(){
    temp_secondary_sensor = 25;
}
