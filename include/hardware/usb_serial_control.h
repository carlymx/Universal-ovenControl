/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <hardware/lcd1602_custom_char.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// LCD1602 I2C [ adress: 0x27 ]
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//==================================//
//           FUNCTIONS:             //
//==================================//

void usb_serial_init(){
    Serial.begin(BAUDRATE);
    Serial.print("STARTING Universal ovenCONTROL\n");
    Serial.print("Min Temp: " +String(MIN_TEMP_COOK) +" - Max Temp: " +String(MAX_TEMP_COOK) +"\n");
}    

void screen_clear(){

}

void screen_refresh(){

}

void screen_text(String msg){

}

void screen_resistances(byte resist){

}

void screen_current_temp(int temp){

}

void screen_back_light(bool active){
  lcd.backlight();
}

void screen_prog_temp(int temp){

}