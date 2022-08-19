/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#if defined LGT8F328P           // FOR LGT8F328P (ARDUINO COMPATIBLE)
    #include <boards/LGT8F328P/configuration_pins.h>
#elif defined RASPBERRYPI_PICO  // FOR RASPBERRY PI PICO /W
    #include <boards/RPi_pico/configuration_pins.h>
#elif defined ARDUINO_BOARDS    // FOR ARDUINO AVR BOARDS (UNO, NANO, MINI...)
    #include <boards/arduino/configuration_pins.h>
#endif


//===========================================
//         HARDWARE CONFIGURATION:          =
//===========================================

#define AC_HERTZ    50      // 50/60 HERTZ

#if defined RASPBERRYPI_PICO || defined LGT8F328P    // ANALOG DIGITAL CONVERTER (12bits=4096 [0-4095])
    #define ADC_BITS    12
#else
    #define ADC_BITS    10  // ANALOG DIGITAL CONVERTER (10bits=1024 [0-1023]), ARDUINO UNO,MINI, MEGA...)
#endif
#define ADC_RATE    pow(2, ADC_BITS)

// CONFIGURE ANALOG INPUTS HARDWARE:
#define ANALOG_R1      680
#define ANALOG_R2      680
#define VOLTAGE_REF      5
#define ADC_VALUE_B01 = ADC_RATE;  //1024,512...
#define ADC_VALUE_B02 = (ADC_RATE(ANALOG_R1/(ANALOG_R1+ANALOG_R2)VOLTAGE_REF)/VOLTAGE_REF);
#define DELTA_INPUT     10

#define PWM_BITS    8       // 256 [0...255]
#define PWM_RATE    pow(2, PWM_BITS)

#define PRIMARY_SENSOR                PIN_TEMP_SENSOR_01  // SELECT ORIGINAL TERMISTOR OVEN SENSOR
#define SECONDARY_SENSOR              PIN_TEMP_SENSOR_02  // SELECT TERMISTOR NTC3950 100K
#define RESISTANCE_SECONDARY_SENSOR     4700              
#define THERMISTOR_SECONDARY_TEMP         25
#define THERMISTOR_SECONDARY_RESIST   100000              // FOR NTC3950-100KOhms 
#define THERMISTOR_SECONDARY_BETA       3950              // FOR NTC3950-100KOhms
#define PULLUP_SECONDARY                   0              // PULLDOWN = 0 / PULLUP = 1

#define MAX_TEMPERATURE                  250              // 250ºC MAX TEMPERATURE SEGURITY LOCK

#define TIME_UFAST_CLICK  100    // IN ms - DEFAULT = 100 (0.1 seg)
#define TIME_FAST_CLICK     5    // UFAST MULTIPLIER - DEFAULT = 5 (0.5 seg)
#define TIME_FULL_CLICK    50    // UFAST MULTIPLIER - DEFAULT = 50 (5 seg)

#define TIMER_INACTIVE    30000  // IN ms 


//===========================================
//       COMUNICATIONS CONFIGURATION:       =
//===========================================

#define USB_SERIAL_PORT
    #ifdef USB_SERIAL_PORT
        #define BAUDRATE    9600    // SERIAL CONEXION [2400, 9600, 19200, 38400, 57600, 115200, 250000, 500000, 1000000]
    #endif

#define SCREEN_CONTROL
    #define LCD_1602_I2C
    //#define OLED_12832_I2C
    //#define OLED_12864_I2C

        #ifdef LCD_1602_I2C
            // EMPTY AT TH MOMENT
        #endif
        #ifdef OLED_12832_I2C
            // EMPTY AT TH MOMENT
        #endif
        #ifdef OLED_12864_I2C
            // EMPTY AT TH MOMENT
        #endif


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
#define COOL_FAN_TEMPERATURE_20     70      // ºC
#define COOL_FAN_TEMPERATURE_33    100      // ºC
#define COOL_FAN_TEMPERATURE_50    150      // ºC
#define COOL_FAN_TEMPERATURE_66    200      // ºC
#define COOL_FAN_TEMPERATURE_75    225      // ºC
#define COOL_FAN_TEMPERATURE_100   250      // ºC


// COEFFICIENTS STEINHART-HART 
//(https://tinyurl.com/SHH-Calculator - https://tinyurl.com/SSH-MultiCalculator)
float c1 = 0.4393641565e-3;       // COEFFICIENT A NTC 25/50 Beta3950 100KOhms
float c2 = 2.531626655e-4;        // COEFFICIENT B NTC 25/50 Beta3950 100KOhms
float c3 = 0.00006146459005e-7;   // COEFFICIENT C NTC 25/50 Beta3950 100KOhms


//===========================================
//         MISCELLANY CONFIGURATION:        =
//===========================================

// #define BOARD_TEST       // IF ACTIVATED, BOARD IN TEST MODE (DESACTIVATE DEFAULT)
// #define DEBUG_LOG        // IF ACTIVATED, SERIAL.PRINT FOR DEBUGING