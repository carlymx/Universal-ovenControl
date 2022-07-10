/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/
#include <melodys.h>

unsigned long timer_counter_00 = millis();      // GLOBAL
unsigned long timer_counter_01 = timer_counter_00;      // FULL TIMER ACTION COUNTER
unsigned long timer_counter_02 = timer_counter_00;      // FAST TIMER ACTION COUNTER
float res_temp01, res_temp02, log_res_temp;
float temp_sensor_01;       // TEMPERATURE SENSOR 01
float temp_sensor_02;       // TEMPERATURE SENSOR 02
bool FULL_CLICK = false;    // FULL TIME_CLICK ACTIONS (1/1)
bool FAST_CLICK = false;    // FAST TIME_CLICK ACTIONS (1/4)

//==========================================
//                FUNCTIONS                =
//==========================================

void control_pcb_fan(){
    if (temp_sensor_01 <= 0){
        analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_100);
        Serial.print("¡¡¡ ATENCION: NO SE HA ENCONTRADO SENSOR TEMPERATURA A1 !!! \n");
        if (_timer_melody == 0xffffffff){start_melody(&ALARM_MELODY);}}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_100){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_100);}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_75){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_75);}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_66){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_66);}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_50){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_50);}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_50){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_50);}
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_33){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_33);}            
    else if (temp_sensor_01 >= COOL_FAN_TEMPERATURE_20){
            analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_20);}
    else {analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_0);}
    return;
}

void open_door(){
    if(PIN_OPEN_DOOR == 1){
        digitalWrite(PIN_LIGHT_CHAMBER, HIGH);
        Serial.print("PUERTA ABIERTA \n");
    }
    else {
        digitalWrite(PIN_LIGHT_CHAMBER, LOW);
        Serial.print("PUERTA CERRADA \n");
        }
    return;
}


void read_temperature_A1(){
    int temp_sensor_01_in = analogRead(PIN_TEMP_SENSOR_01);    // READ TERMISTOR A1
    res_temp01 = RESISTANCE_TEMP_SENSOR_01 * (ADC_RATE / (float)temp_sensor_01_in - 1.0); // TENSION TO RESISTENCE 
    log_res_temp = log(res_temp01);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor_01 = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor_01 = temp_sensor_01 - 273.15;   // CELSIUS

    Serial.println("Sensor A1: " + (String)temp_sensor_01);
    return;
}


void read_temperature_A2(){
    int temp_sensor_02_in = analogRead(PIN_TEMP_SENSOR_02);    // READ TERMISTOR A2
    res_temp02 = RESISTANCE_TEMP_SENSOR_02 * (ADC_RATE / (float)temp_sensor_02_in - 1.0); // TENSION TO RESISTENCE 
    log_res_temp = log(res_temp02);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor_02 = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor_02 = temp_sensor_02 - 273.15;   // CELSIUS

    Serial.println("Sensor A2: " + (String)temp_sensor_02);
    return;
}


void time_click() {
    timer_counter_00 = millis();

    // ANTI OVERFLOW (UNSIGNED LONG, 50 DAYS)
    if (timer_counter_00 < timer_counter_01){
        timer_counter_00 = millis();
        timer_counter_01 = timer_counter_00;
        timer_counter_02 = timer_counter_00;
    }

    // FAST ACTIONS TIMER
    if (timer_counter_00 >= timer_counter_02){
        FAST_CLICK = true;
        timer_counter_02 = millis() + TIME_CLICK/4;
    }
    else {
        FAST_CLICK = false;
    }
    
    // FULL ACTION TIMER
    if (timer_counter_00 > timer_counter_01){
        FULL_CLICK = true;
        timer_counter_01 = millis() + TIME_CLICK;
    }
    else {
        FULL_CLICK = false;
    }
    return;
}