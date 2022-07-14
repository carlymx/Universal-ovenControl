/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//              EEPROM CONFIG:              =
//===========================================

/* THIS WILL ERASE THE ENTIRE CONTENT OF THE 
EEPROM (WRITE ALL 0'S) AND FORMAT IT WITH THE 
DATA REQUIRED FOR A FIRST START-UP. */

#define EEPROM_CRC_CONTROL      123     // ALEATORY NUMBER FOR ADDITION CRC
#define PROJECT_NAME            "openELECTRO: oven CONTROL"
#define PROJECT_VERSION         "v0.60a"
#define PROJECT_URL             "https://github.com/carlymx/openELECTRO"
#define PROJECT_TEMP_IN         "ºC"

#define TEMP_INTERVAL 5
#define TEMP_INI 0
#define TEMP_FIN 250 
#define TEMP_NUM ((TEMP_FIN - TEMP_INI) / TEMP_INTERVAL) + 1

// EEPROM STRUCTURE:
struct program_eeprom {
    byte lon_temp;
    byte temp_obj[TEMP_NUM];
    bool mapped01;
    int temp_map01[TEMP_NUM];
};

// OBJECT IMPLEMENTATION
struct program_eeprom prog_eeprom_actual;

void init_program_eeprom(program_eeprom* a){
    a->lon_temp = TEMP_NUM;
    a->mapped01 = false;

    // Tabla de temperaturas cada 5 grados    
    for (int i = TEMP_INI / TEMP_INTERVAL; i < TEMP_NUM; i++) {
        a->temp_obj[i] = i * TEMP_INTERVAL;
        a->temp_map01[i] = 0;
    }
}

#ifdef ARDUINO_BOARDS
    #include <arduino/fnc_eeprom.h>
#else
    #include <RPi_pico/fnc_eeprom.h>
#endif

