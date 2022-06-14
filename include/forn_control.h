/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

unsigned long timer_counter_00 = millis();
unsigned long timer_counter_01 = millis();
float res_temp, log_res_temp;
float temp_sensor_01;   // TEMPERATURE SENSOR 01
float temp_sensor_02;   // TEMPERATURE SENSOR 02


//==========================================
//        PREVIOUS CALCULATIONS            =
//==========================================

// ANALOG DIGITAL CONVERTER bits: [10 bits = 1023, 12 = 4095...]
int adc_rate = (pow(2, ANALOG_DIGITAL_CONVERTER_BITS) - 1);

//==========================================
//                FUNCTIONS                =
//==========================================

void read_temperature_A1(){
    int temp_sensor_01_in = analogRead (PIN_TEMP_SENSOR_01);    // READ TERMISTOR A1
    res_temp = RESISTANCE_TEMP_SENSOR_01 * (adc_rate / (float)temp_sensor_01_in - 1.0); // TENSION TO RESISTENCE 
    log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor_01 = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor_01 = temp_sensor_01 - 273.15;   // CELSIUS

    Serial.println("Sensor A1: " + (String)res_temp + " - " + (String)temp_sensor_01_in + " - " + (String)temp_sensor_01);
}


void read_temperature_A2(){
    int temp_sensor_02_in = analogRead (PIN_TEMP_SENSOR_02);    // READ TERMISTOR A2
    res_temp = RESISTANCE_TEMP_SENSOR_02 * (adc_rate / (float)temp_sensor_02_in - 1.0); // TENSION TO RESISTENCE 
    log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor_02 = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor_02 = temp_sensor_02 - 273.15;   // CELSIUS

    Serial.println("Sensor A2: " + (String)res_temp + " - " + (String)temp_sensor_02_in + " - " + (String)temp_sensor_02);
}


void time_space() {
    timer_counter_01 = millis();

    // ANTI OVERFLOW (UNSIGNED LONG, 50 DAYS)
    if (timer_counter_01 < timer_counter_00){
        timer_counter_00 = millis();
        timer_counter_01 = millis();
    }

    if (timer_counter_01 > (timer_counter_00 + SENSOR_TIME_SPACE)){
        read_temperature_A1();
        read_temperature_A2();
        timer_counter_00 = millis();
     }
}     