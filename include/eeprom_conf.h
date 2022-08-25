/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//              EEPROM CONFIG:              =
//===========================================

/* THIS WILL ERASE THE ENTIRE CONTENT OF THE 
EEPROM (WRITE ALL 0'S) AND FORMAT IT WITH THE 
DATA REQUIRED FOR A FIRST START-UP. */

#define EEPROM_CRC_CONTROL      123     // ALEATORY NUMBER FOR ADDITION CRC
//#define PROJECT_NAME            "Universal ovenCONTROL"
//#define PROJECT_VERSION         "v0.92b"
//#define PROJECT_URL             "https://github.com/carlymx/Universal-ovenControl"
//#define PROJECT_TEMP_IN         "ºC"

#define TEMP_INTERVAL 5
#define TEMP_INI 30
#define TEMP_FIN 255 
#define TEMP_NUM ((TEMP_FIN - TEMP_INI) / TEMP_INTERVAL) + 1

#define EEPROM_OPT_MAPPED     1
#define EEPROM_OPT_DESCENDING 2

// EEPROM STRUCTURE:
struct program_eeprom {
    byte lon_temp;
    byte options;
    int temp_map01[TEMP_NUM];
};

// OBJECT IMPLEMENTATION
struct program_eeprom prog_eeprom_actual;

void init_program_eeprom(program_eeprom* a){
    a->lon_temp = TEMP_NUM;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    a->options = 0;

    // Tabla de temperaturas cada 5 grados    
    for (byte i = TEMP_INI / TEMP_INTERVAL; i < TEMP_NUM; i++) {
        a->temp_map01[i] = 0;
    }
}

#if defined LGT8F328P
    #include <boards/LGT8F328P/fnc_eeprom.h>
#elif defined RASPBERRYPI_PICO
    #include <boards/RPi_pico/fnc_eeprom.h>
#elif defined ARDUINO_BOARDS
    #include <boards/arduino/fnc_eeprom.h>
#endif