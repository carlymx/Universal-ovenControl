/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

unsigned long timer_counter_00 = millis();      // GLOBAL
unsigned long timer_counter_01 = timer_counter_00;      // FULL TIMER ACTION COUNTER
unsigned long timer_counter_02 = timer_counter_00;      // FAST TIMER ACTION COUNTER
// float res_temp01, res_temp02, log_res_temp;
float temp_sensor_01;       // TEMPERATURE SENSOR 01
float temp_sensor_02;       // TEMPERATURE SENSOR 02
bool FULL_CLICK = false;    // FULL TIME_CLICK ACTIONS (1/1)
bool FAST_CLICK = false;    // FAST TIME_CLICK ACTIONS (1/4)

int temp_oven [] = {
    COOL_FAN_TEMPERATURE_100, COOL_FAN_TEMPERATURE_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50, 
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

unsigned int power_fan [] = {
    PWM_CONTROL_POWER_100, PWM_CONTROL_POWER_75, PWM_CONTROL_POWER_66, PWM_CONTROL_POWER_50,
    PWM_CONTROL_POWER_33, PWM_CONTROL_POWER_20, PWM_CONTROL_POWER_0
};

//==========================================
//                FUNCTIONS                =
//==========================================

byte control_pcb_fan() {
    byte err = 0;

    if (temp_sensor_01 <= 0){
        analogWrite(PIN_PCB_FAN, PWM_CONTROL_POWER_100);
        // Serial.print("¡¡¡ ATENCION: NO SE HA ENCONTRADO SENSOR TEMPERATURA A1 !!! \n");
        err = 1;
        // if (_timer_melody == 0xffffffff){start_melody(&ALARM_MELODY);
    }
    else {
        for (int i = sizeof(temp_oven) - 1; i >= 0; i--)
        {
            if (temp_sensor_01 >= temp_oven[i]) {
                analogWrite(PIN_PCB_FAN, power_fan[i]);
                break;
            }
        }            
    }
    
    return err;
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

int read_temperature (byte pin, long resistance){
    int temp_sensor = analogRead(pin);    // READ TERMISTOR 
    float res_temp = resistance * (ADC_RATE / (float)temp_sensor); // TENSION TO RESISTENCE 
    float log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    temp_sensor = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    temp_sensor = temp_sensor - 273.15;   // CELSIUS

    return temp_sensor;
}

void read_temperature_A1(){
    temp_sensor_01 = read_temperature(PIN_TEMP_SENSOR_01, RESISTANCE_TEMP_SENSOR_01); 
    Serial.println("Sensor A1: " + String(temp_sensor_01));
}

void read_temperature_A2(){
    temp_sensor_02 = read_temperature(PIN_TEMP_SENSOR_02, RESISTANCE_TEMP_SENSOR_02); 
    Serial.println("Sensor A2: " + String(temp_sensor_02));
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