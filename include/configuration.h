/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

#ifdef ARDUINO_BOARDS   // FOR ARDUINO AVR BOARDS (UNO, NANO, MINI...)
    #include <arduino/configuration_pins.h>
#else                   // FOR RASPBERRY PI PICO /W
    #include <RPi_pico/configuration_pins.h>
#endif

//===========================================
//         HARDWARE CONFIGURATION:          =
//===========================================

#define BAUDRATE    9600    // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]

#ifdef RASPBERRYPI_PICO     // ANALOG DIGITAL CONVERTER (12bits=4096 [0-4095])
    #define ADC_BITS    12
#else
    #define ADC_BITS    10  // ANALOG DIGITAL CONVERTER (10bits=1024 [0-1023]), ARDUINO UNO,MINI, MEGA...)
#endif
#define ADC_RATE    (pow(2, ADC_BITS) - 1)
#define PWM_BITS    8       // 256 [0...255]

#define PRIMARY_SENSOR                PIN_TEMP_SENSOR_01  // SELECT ORIGINAL TERMISTOR OVEN SENSOR
#define SECUNDARY_SENSOR              PIN_TEMP_SENSOR_02  // SELECT TERMISTOR NTC3950 100K
#define PRIMARY_SENSOR_DUMMY          true       // IF SENSOR DUMMY, THE SENSOR ALWAYS RETURNS 20ºC
#define SECUNDARY_SENSOR_DUMMY        true       // IF SENSOR DUMMY, THE SENSOR ALWAYS RETURNS 25ºC
#define RESISTANCE_PRIMARY_SENSOR     100000     // 100KOhms
#define RESISTANCE_SECUNDARY_SENSOR   100000     // 100KOhms
#define MAX_TEMPERATURE               250        // 250ºC MAX TEMPERATURE SEGURITY LOCK

#define TIME_CLICK  5000    // IN ms - DEFAULT = 5000 (5 seg)

#define AC_HERTZ    50      // 50/60 HERTZ

//===========================================
//         PROGRAM CONFIGURATION:           =
//===========================================

//CONTROL % PWM FANs CONFIGURATION:
#define PWM_CONTROL_POWER_0     (unsigned int)((pow(2,(byte)PWM_BITS)/100)* 0)
#define PWM_CONTROL_POWER_20    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*20)
#define PWM_CONTROL_POWER_33    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*33)
#define PWM_CONTROL_POWER_50    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*50)
#define PWM_CONTROL_POWER_66    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*66)
#define PWM_CONTROL_POWER_75    (unsigned int)((pow(2,(byte)PWM_BITS)/100)*75)
#define PWM_CONTROL_POWER_100   (unsigned int)(pow(2,(byte)PWM_BITS)-1)

//CONTROL % DIMMER CONFIGURATION: (in microseg)
#define DIMMER_CONTROL_POWER_0     (unsigned int)(((1000000UL/AC_HERTZ)*  0)/200)
#define DIMMER_CONTROL_POWER_20    (unsigned int)(((1000000UL/AC_HERTZ)* 20)/200)
#define DIMMER_CONTROL_POWER_33    (unsigned int)(((1000000UL/AC_HERTZ)* 33)/200)
#define DIMMER_CONTROL_POWER_50    (unsigned int)(((1000000UL/AC_HERTZ)* 50)/200)
#define DIMMER_CONTROL_POWER_66    (unsigned int)(((1000000UL/AC_HERTZ)* 66)/200)
#define DIMMER_CONTROL_POWER_75    (unsigned int)(((1000000UL/AC_HERTZ)* 75)/200)
#define DIMMER_CONTROL_POWER_100   (unsigned int)(((1000000UL/AC_HERTZ)*100)/200)

// TEMPERATURE ACTIVATORS % to ºC
#define COOL_FAN_TEMPERATURE_20    70       // ºC
#define COOL_FAN_TEMPERATURE_33    100      // ºC
#define COOL_FAN_TEMPERATURE_50    150      // ºC
#define COOL_FAN_TEMPERATURE_66    200      // ºC
#define COOL_FAN_TEMPERATURE_75    225      // ºC
#define COOL_FAN_TEMPERATURE_100   250      // ºC


// COEFFICIENTS STEINHART-HART (https://tinyurl.com/SHH-Calculator)
float c1 = 2.114990448e-03;     // DEFAULT FOR NPC 100KOhms
float c2 = 0.3832381228e-04;    // DEFAULT FOR NPC 100KOhms
float c3 = 5.228061052e-07;     // DEFAULT FOR NPC 100KOhms

//===========================================
//         MISCELLANY CONFIGURATION:        =
//===========================================

// #define BOARD_TEST       // IF ACTIVATED, BOARD IN TEST MODE (DESACTIVATE DEFAULT)
// #define FORMAT_EEPROM    // IF ACTIVATED, ERASE EEPROM AND FORMAT
