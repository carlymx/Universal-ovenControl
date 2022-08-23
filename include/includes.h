/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// LIB INCLUDE
#include <Arduino.h>
#include <math.h>

#include <version.h>
//#include <resourcestrings_en.h>
#include <resourcestrings_es.h>
#include <configuration.h>
#include <eeprom_conf.h>
#include <global_vars.h>
#include <text_funcs.h>
#include <melodys.h>
#include <temperature_func.h>
#include <timer_control.h>
#include <debuglog_funcs.h>

//======================================
//            MISC INCLUDES:           =
//======================================

#if defined BOARD_TEST          // TEST MODE
  #include <board_test.h>
  byte last_input = 0;
#elif defined FORMAT_EEPROM     // FORMAT MODE
  // EMPTY AT THE MOMENT
#else                           // NORMAL MODE
  // EMPTY AT THE MOMENT
#endif

//======================================
//       COMUNICATIONS INCLUDES:       =
//======================================

#if defined USB_SERIAL_PORT
    #include <hardware/usb_serial_control.h>
#endif

//#if defined SCREEN_CONTROL
    #ifdef SCREEN_SERIAL
      #include <hardware/lcdserial_control.h>
    #endif
    #ifdef SCREEN_SERIAL_1602
      #include <hardware/lcd1602_serial.h>
    #endif
    #if defined LCD_1602_I2C
        #include <hardware/lcd1602_LiquidCrystal_I2C.h>
    #endif
    #ifdef OLED_12832_I2C
        #include <hardware/lcd1602_SSD1306.h>
    #endif
    #ifdef OLED_12864_I2C
        // EMPTY AT TH MOMENT
    #endif
//#else
//  #include <hardware/lcdserial_control.h>
//#endif

//======================================
//          HARDWARE INCLUDES:         =
//======================================

#if defined DUMMY_SENSORS
  #include <test/inputs_control.h>
  #include <test/temperature_control.h>
#else
  #include <hardware/inputs_control.h>
  #include <hardware/temperature_control.h>
#endif

#include <hardware/resistance_control.h>
#include <hardware/zero_crossing_control.h>
#include <hardware/dimmer_control.h>
#include <hardware/fan_control.h>
#include <hardware/light_control.h>
#include <oven_control.h>

//======================================
//      STATE MACHINES INCLUDES:       =
//======================================

#include <statemachines/cooking.h>
#include <statemachines/setup.h>
