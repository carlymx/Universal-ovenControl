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

#include <configuration.h>
#include <eeprom_conf.h>
#include <global_vars.h>
#include <melodys.h>
#include <hardware/inputs_control.h>

#if defined BOARD_TEST          // TEST MODE
  #include <board_test.h>
  byte last_input = 0;
#elif defined FORMAT_EEPROM     // FORMAT MODE
  // EMPTY AT THE MOMENT
#else                           // NORMAL MODE
  // EMPTY AT THE MOMENT
#endif

//======================================
//          HARDWARE INCLUDES:         =
//======================================

#include <hardware/resistance_control.h>
#include <hardware/zero_crossing_control.h>
#include <hardware/dimmer_control.h>
#include <hardware/temperature_control.h>
#include <hardware/fan_control.h>
#include <hardware/light_control.h>
#include <oven_control.h>

//======================================
//      STATE MACHINES INCLUDES:       =
//======================================

#include <statemachines/cooking.h>
#include <statemachines/calibrate.h>

//======================================
//       COMUNICATIONS INCLUDES:       =
//======================================

#ifdef USB_SERIAL_PORT
    #include <hardware/usb_serial_control.h>
#endif

#if defined SCREEN_CONTROL
    #if defined LCD_1602_I2C
        #include <Wire.h>
        #include <LiquidCrystal_I2C.h>
        #include <hardware/lcd1602_control.h>
    #endif
    #ifdef OLED_12832_I2C
        // EMPTY AT TH MOMENT
    #endif
    #ifdef OLED_12864_I2C
        // EMPTY AT TH MOMENT
    #endif
#endif