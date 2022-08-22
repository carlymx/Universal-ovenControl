/***************************************************************  
    openELECTRO
    Home appliance oven control, based on arduino and other MPU

    https://github.com/carlymx/Universal-ovenControl
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#if defined LGT8F328P           // FOR LGT8F328P (ARDUINO COMPATIBLE)
    #include <boards/LGT8F328P/hardware_conf.h>
#elif defined RASPBERRYPI_PICO  // FOR RASPBERRY PI PICO /W
    #include <boards/rasberryPICO/hardware_conf.h>
#elif defined ARDUINO_BOARDS    // FOR ARDUINO AVR BOARDS (UNO, NANO, MINI...)
    #include <boards/arduino/hardware_conf.h>
#endif