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

// ARDUINO NANO PINOUT COMPATIBLE:
// OUTPUTS RELAYS:
#define PIN_LIGHT_CHAMBER   12      // ON/OFF - RELAY
#define PIN_RESISTOR_UP     11      // ON/OFF - RELAY
#define PIN_RESISTOR_DOWN   8       // ON/OFF - RELAY
#define PIN_RESISTOR_REAR   7       // ON/OFF - RELAY
// OUTPUTS DIMMER:
#define PIN_COOL_FAN        10      // 50/60Hz AC DIMMER CONTROL
#define PIN_CHAMBER_FAN     9       // 50/60Hz AC DIMMER CONTROL
// PCB CONTROL:
#define PIN_PCB_FAN         6       // PCB FAN (PWM PIN REQUIRED)
#define PIN_SPEEKER         5       // Piezoelectric Speaker (PWM PIN REQUIRED)
// COMMUNICATIONS:
#define PIN_ESP8266_RX      3       // RX WIFI ESP8266 PORT
#define PIN_BT_HC05_RX      13      // RX BLUETOOTH PORT 
#define PIN_I2C_SDA         PIN_A4  // I2C PORT
#define PIN_I2C_SCL         PIN_A5  // I2C PORT
// INPUTS:
#define PIN_OPEN_DOOR       4       // ON/OFF (1 CLOSE, 0 OPEN)
#define PIN_ZERO_CROSSING   2       // 50/60Hz AC ZERO_CROSSING INTERRUPT
#define PIN_TEMP_SENSOR_01  PIN_A6  // ANALOG SENSOR IN
#define PIN_TEMP_SENSOR_02  PIN_A7  // ANALOG SENSOR IN
#define PIN_PUSH_00         PIN_A0  // PUSH BUTTON INPUT
#define PIN_PUSH_01         PIN_A1  // PUSH BUTTON INPUT
#define PIN_PUSH_02         PIN_A2  // PUSH BUTTON INPUT
#define PIN_PUSH_03         PIN_A3  // PUSH BUTTON INPUT



//===========================================
//         PROGRAM CONFIGURATION:           =
//===========================================


#define BAUDRATE    9600   // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
#define ANALOG_DIGITAL_CONVERTER_BITS   10    // 10 bits ARDUINO UNO,MINI, MEGA...
#define PWM_BITS    8   // 256 [0...255]

#define RESISTANCE_TEMP_SENSOR_01   100000     // 100KOhms
#define RESISTANCE_TEMP_SENSOR_02   100000     // 100KOhms

#define TIME_CLICK      5000    // 5 SEG


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