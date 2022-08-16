#define ADC_BITS    10  // ANALOG DIGITAL CONVERTER (10bits=1024 [0-1023]), ARDUINO UNO,MINI, MEGA...)
#define ADC_RATE    pow(2, ADC_BITS)

#define RESISTANCE_SECONDARY_SENSOR     4700              
#define THERMISTOR_SECONDARY_TEMP         25
#define THERMISTOR_SECONDARY_RESIST   100000              // FOR NTC3950-100KOhms 
#define THERMISTOR_SECONDARY_BETA       3950              // FOR NTC3950-100KOhms
#define PULLUP_SECONDARY                   0              // PULLDOWN = 0 / PULLUP = 1

// COEFFICIENTS STEINHART-HART 
//(https://tinyurl.com/SHH-Calculator - https://tinyurl.com/SSH-MultiCalculator)
float c1 = 0.4393641565e-3;       // COEFFICIENT A NTC 25/50 Beta3950 100KOhms
float c2 = 2.531626655e-4;        // COEFFICIENT B NTC 25/50 Beta3950 100KOhms
float c3 = 0.00006146459005e-7;   // COEFFICIENT C NTC 25/50 Beta3950 100KOhms

// ******* eeprom_fnc.h ********

#define TEMP_INTERVAL 5
#define TEMP_INI 0
#define TEMP_FIN 255 
#define TEMP_NUM ((TEMP_FIN - TEMP_INI) / TEMP_INTERVAL) + 1

// EEPROM STRUCTURE:
struct program_eeprom {
    byte lon_temp;
    bool mapped01;
    int temp_map01[TEMP_NUM];
};

// OBJECT IMPLEMENTATION
struct program_eeprom prog_eeprom_actual;

void init_program_eeprom(program_eeprom* a){
    a->lon_temp = TEMP_NUM;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    a->mapped01 = false;

    // Tabla de temperaturas cada 5 grados    
    for (byte i = TEMP_INI / TEMP_INTERVAL; i < TEMP_NUM; i++) 
        a->temp_map01[i] = 0;
    
}

// ************ temperature_func.h ***************

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

/*
int read_temperature_map(int raw_temp, program_eeprom* prog) {
    for (unsigned int i=0; i<prog->lon_temp; i++){
        if (raw_temp <= prog->temp_map01[i]) 
            return TEMP_INI + ((i == 0 ? 0 : i-1) * TEMP_INTERVAL);
    } 

    return TEMP_FIN;
}
*/

// calibrate.h

byte last_input_calibrate = 0;
byte cur_idx_calibrate = 0;

int current_temp_secondary = 0;
int raw_primary_sensor = 0;

void set_map_temp(program_eeprom *prog) {
    while((cur_idx_calibrate < TEMP_NUM) && (TEMP_INI + (cur_idx_calibrate * TEMP_INTERVAL) <= current_temp_secondary)){
        prog->temp_map01[cur_idx_calibrate] = raw_primary_sensor;
        Serial.print(TEMP_INI + (cur_idx_calibrate * TEMP_INTERVAL));
        Serial.print(": ");
        Serial.println(prog->temp_map01[cur_idx_calibrate]);
        cur_idx_calibrate++;
    }
}

void calibrate_finish(){
  prog_eeprom_actual.mapped01 = true;
  Serial.println("prog_eeprom_actual.temp_map01 = {");
  for(int i = 0; i<TEMP_NUM; i++) {
    Serial.print(prog_eeprom_actual.temp_map01[i]);
    Serial.print(", ");    
  }               
  Serial.println("}");               
}

void calibrate_temp_change(int rawvalue){
    raw_primary_sensor = rawvalue;
    current_temp_secondary = read_temperature(rawvalue, RESISTANCE_SECONDARY_SENSOR, c1, c2, c3, PULLUP_SECONDARY == 1);
    set_map_temp(&prog_eeprom_actual);
  
    if(cur_idx_calibrate >= TEMP_NUM) calibrate_finish();    
}

void start_calibration(){
  init_program_eeprom(&prog_eeprom_actual); // reseteamos actual
}


void print_temp(int rawvalue) {
  Serial.print(rawvalue);
  Serial.print(" = ");
  Serial.print(read_temperature(rawvalue, RESISTANCE_SECONDARY_SENSOR, c1, c2, c3, PULLUP_SECONDARY == 1));
  Serial.print(" = ");
  Serial.println(read_temperature_beta(rawvalue, RESISTANCE_SECONDARY_SENSOR, THERMISTOR_SECONDARY_RESIST, 
                                       THERMISTOR_SECONDARY_TEMP, THERMISTOR_SECONDARY_BETA, PULLUP_SECONDARY == 1)); 
  
}

int i = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  start_calibration();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100); // Wait for 1000 millisecond(s)
  
  if(i<1024){
    //print_temp(i);
    calibrate_temp_change(i);
    i+=4;
  }
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); // Wait for 1000 millisecond(s)
  
}