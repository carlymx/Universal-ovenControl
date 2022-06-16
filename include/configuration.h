/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//            PIN CONFIGURATION:            =
//===========================================

#define PIN_LED_INDICATOR   13      // 0/1
#define PIN_LIGHT_CHAMBER   12      // 0/1
#define PIN_RESISTOR_UP     11      // 0/1
#define PIN_RESISTOR_DOWN   10      // 0/1
#define PIN_RESISTOR_REAR   9       // 0/1
#define PIN_COOL_FAN        8       // PWM
#define PIN_CHAMBER_FAN     7       // PWM
#define PIN_PCB_FAN         6       // PWM
#define PIN_SPEEKER         5       // PWM - Piezoelectric Speaker
#define PIN_OPEN_DOOR       4       // 0/1
#define PIN_ESP8266_RX      3       // RX SERIAL PORT
#define PIN_ESP8266_TX      2       // TX SERIAL PORT
#define PIN_TEMP_SENSOR_01  PIN_A0  // ANALOG IN
#define PIN_TEMP_SENSOR_02  PIN_A1  // ANALOG IN
#define PIN_I2C_SDA         PIN_A4  // I2C PORT
#define PIN_I2C_SCL         PIN_A5  // I2C PORT



//===========================================
//         PROGRAM CONFIGURATION:           =
//===========================================


#define BAUDRATE    9600   // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
#define ANALOG_DIGITAL_CONVERTER_BITS   10    // 10 bits ARDUINO UNO,MINI, MEGA...
#define PWM_BITS    8   // 256 [0...255]

#define RESISTANCE_TEMP_SENSOR_01   100000     // 100KOhms
#define RESISTANCE_TEMP_SENSOR_02   100000     // 100KOhms

#define SENSOR_TIME_SPACE   5000    // 5 SEG


//CONTROL FAN CONFIGURATION:
#define PWM_CONTROL_POWER_0     (unsigned int)((pow(2,(byte)PWM_BITS)/100)*0)
#define PWM_CONTROL_POWER_20    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*20)
#define PWM_CONTROL_POWER_33    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*33)
#define PWM_CONTROL_POWER_50    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*50)
#define PWM_CONTROL_POWER_66    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*66)
#define PWM_CONTROL_POWER_75    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*75)
#define PWM_CONTROL_POWER_100   (unsigned int)(pow(2,(byte)PWM_BITS))

#define COOL_FAN_TEMPERATURE_20    70       // ºC
#define COOL_FAN_TEMPERATURE_33    100      // ºC
#define COOL_FAN_TEMPERATURE_50    150      // ºC
#define COOL_FAN_TEMPERATURE_66    200      // ºC
#define COOL_FAN_TEMPERATURE_75    225      // ºC
#define COOL_FAN_TEMPERATURE_100   250      // ºC




// coefficients Steinhart-Hart:
// https://tinyurl.com/SHH-Calculator
float c1 = 2.114990448e-03;                     // NPC 100KOhms
float c2 = 0.3832381228e-04;                    // NPC 100KOhms
float c3 = 5.228061052e-07;                     // NPC 100KOhms