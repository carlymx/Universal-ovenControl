/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// DUMMY MODE

void read_temperature_primary() {
    if (resistance_active == true) temp_primary_sensor += 5;
    else temp_primary_sensor -= 4;

    if (temp_primary_sensor < 20) temp_primary_sensor = 20;

    if (current_temp_primary != temp_primary_sensor){
        current_temp_primary = temp_primary_sensor;
        temp_change_primary = true;
        Serial.println("Primary Sensor (DUMMY): " + String(current_temp_primary));
    }
}

void read_temperature_secundary(){
    if (resistance_active == true) temp_secondary_sensor += 5;
    else temp_secondary_sensor -= 4;

    if (temp_secondary_sensor < 20) temp_secondary_sensor = 20;

    if (temp_secondary_sensor != temp_secondary_sensor){
        temp_secondary_sensor = temp_secondary_sensor;
        temp_secondary_sensor = true;
        Serial.println("Secondary Sensor (DUMMY): " + String(temp_secondary_sensor));
    }
}