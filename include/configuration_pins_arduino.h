/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//        ARDUINO PIN CONFIGURATION:        =
//===========================================

// DEFAULT = ARDUINO NANO PINOUT COMPATIBLE:
// OUTPUTS RELAYS:
#define PIN_LIGHT_CHAMBER   12      // ON/OFF - RELAY
#define PIN_RESISTOR_UP     11      // ON/OFF - RELAY
#define PIN_RESISTOR_DOWN   8       // ON/OFF - RELAY
#define PIN_RESISTOR_REAR   7       // ON/OFF - RELAY
// OUTPUTS DIMMER:
#define PIN_COOL_FAN        10      // 50/60Hz AC DIMMER CONTROL
#define PIN_CHAMBER_FAN     9       // 50/60Hz AC DIMMER CONTROL
// PCB CONTROL:
#define PIN_PCB_FAN         6       // PCB FAN (PWM PIN REQUIRED) (IN UNO, MINI or NANO: PIN 6 TIMER-0)
#define PIN_SPEEKER         5       // Piezoelectric (PWM PIN REQUIRED) (IN UNO, MINI or NANO: PIN 5 TIMER-0)
// COMMUNICATIONS:
#define PIN_ESP8266_RX      3       // RX WIFI ESP8266 PORT
#define PIN_BT_HC05_RX      13      // RX BLUETOOTH PORT 
#define PIN_I2C_SDA         PIN_A4  // I2C PORT
#define PIN_I2C_SCL         PIN_A5  // I2C PORT
// INPUTS:
#define PIN_OPEN_DOOR       4       // ON/OFF (1 CLOSE, 0 OPEN)
#define PIN_ZERO_CROSSING   2       // 50/60Hz AC ZERO_CROSSING INTERRUPT
#define PIN_PUSH_00         PIN_A0  // PUSH BUTTON INPUT
#define PIN_PUSH_01         PIN_A1  // PUSH BUTTON INPUT
#define PIN_PUSH_02         PIN_A2  // PUSH BUTTON INPUT
#define PIN_PUSH_03         PIN_A3  // PUSH BUTTON INPUT
#define PIN_TEMP_SENSOR_01  PIN_A6  // ANALOG SENSOR IN
#define PIN_TEMP_SENSOR_02  PIN_A7  // ANALOG SENSOR IN