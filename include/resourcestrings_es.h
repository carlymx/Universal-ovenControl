/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
#define RESSTR_APP_NAME       "Univ ovenCONTROL"
#define RESSTR_STARTING       "INICIALIZANDO"

#define RESSTR_SEL_TEMP       "Seleccionar temperatura" 
#define RESSTR_WARM_UP        "Calentando" 
#define RESSTR_COOKING        "Cocinando" 
#define RESSTR_SETUP          "Configuracion" 

#define RESSTR_SETUP_MENU_CALIBRATE      "Calibrate"
#define RESSTR_SETUP_MENU_FORMAT_EEPROM  "Format EEPROM"
#define RESSTR_SETUP_MENU_TEST_FAN       "Test fan"
#define RESSTR_SETUP_MENU_TEST_REAR_FAN  "Test rear fan"
#define RESSTR_SETUP_MENU_TEST_COOL_FAN  "Test cool fan" 
#define RESSTR_SETUP_MENU_DEV_MODE       "Dev mode"  
#define RESSTR_SETUP_MENU_RESET          "Reset"
#define RESSTR_SETUP_MENU_VERSION        "Software version"

#define RESSTR_CALIBRATION_START         "Calibration Start"
#define RESSTR_CALIBRATION_END           "Calibration End"

#define RESSTR_FORMAT_START              "Pulsa + para continuar"
#define RESSTR_FORMAT_EEPROM_END         "EEPROM formateada"

#define RESSTR_OPERATION_CANCELED        "Operacion cancelada"
#define RESSTR_SCREEN_WAIT               "PULSE UNA TECLA PARA EMPEZAR"

#define RESSTR_ENABLED                   "Activo"
#define RESSTR_DISABLED                  "Inactivo"

#if defined DEBUG_LOG_HW || defined DEBUG_LOG
#define RESSTR_MIN_TEMP       "Temp Min" 
#define RESSTR_MAX_TEMP       "Temp Max" 
#define RESSTR_PROG_TEMP      "Temp Prog." 
#define RESSTR_CURR_TEMP      "Temp Actual"
#define RESSTR_COOKING_MODE   "Modo Cocinar" 
#define RESSTR_SETUP_MODE     "Modo Configurar" 
#endif

