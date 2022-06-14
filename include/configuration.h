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

#define PIN_LED_INDICATOR   13
#define PIN_LIGHT_CHAMBER   12
#define PIN_RESISTOR_UP     11
#define PIN_RESISTOR_DOWN   10
#define PIN_RESISTOR_REAR   09
#define PIN_COOL_FAN        08
#define PIN_CHAMBER_FAN     07
#define PIN_PCB_FAN         06
#define PIN_SPEEKER         05
#define PIN_OPEN_DOOR       04
#define PIN_ESP8266_RX      03
#define PIN_ESP8266_TX      02
#define PIN_TEMP_SENSOR_01  PIN_A1
#define PIN_TEMP_SENSOR_02  PIN_A2


//===========================================
//         PROGRAM CONFIGURATION:           =
//===========================================


#define BAUDRATE 9600   // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
#define ANALOG_DIGITAL_CONVERTER_BITS 10    // 10 bits ARDUINO UNO,MINI, MEGA...

#define RESISTANCE_TEMP_SENSOR_01   100000     // 100KOhms
#define RESISTANCE_TEMP_SENSOR_02   100000     // 100KOhms

#define SENSOR_TIME_SPACE   5000    // 5 SEG



// coefficients Steinhart-Hart:
// https://tinyurl.com/SHH-Calculator
float c1 = 2.114990448e-03;                     // NPC 100KOhms
float c2 = 0.3832381228e-04;                    // NPC 100KOhms
float c3 = 5.228061052e-07;                     // NPC 100KOhms