/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

#ifdef ARDUINO_BOARDS
    #include <configuration_pins_arduino.h>
#else
    #include <configuration_pins_raspberry.h>
#endif

//===========================================
//         HARDWARE CONFIGURATION:          =
//===========================================

#define BAUDRATE    9600    // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]

#ifdef RASPBERRYPI_PICO     // ANALOG DIGITAL CONVERTER (10bits=1024 [0-1023]), ARDUINO UNO,MINI, MEGA...)
    #define ADC_BITS    12
#else
    #define ADC_BITS    10
#endif
#define ADC_RATE    (pow(2, ADC_BITS) - 1)
#define PWM_BITS    8       // 256 [0...255]

#define RESISTANCE_TEMP_SENSOR_01   100000     // 100KOhms
#define RESISTANCE_TEMP_SENSOR_02   100000     // 100KOhms
#define MAX_TEMPERATURE                250     // 250ºC MAX TEMPERATURE SEGURITY LOCK

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

// TEMPERATURE ACTIVATORS %
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

// #define BOARD_TEST   // IF ACTIVATED, BOARD IN TEST MODE (DESACTIVATE DEFAULT)
// #define FORMAT_EEPROM   // IF ACTIVATED, ERASE EEPROM AND FORMAT

#ifdef FORMAT_EEPROM
    #define EEPROM_CRC_CONTROL      234     // ALEATORY NUMBER FOR ADDITION CRC
    #define PROJECT_NAME            "openELECTRO: oven CONTROL"
    #define PROJECT_VERSION         "v0.60a"
    #define PROJECT_URL             "https://github.com/carlymx/openELECTRO"
    #define PROJECT_TEMP_IN         "ºC"
#endif