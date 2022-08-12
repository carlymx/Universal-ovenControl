/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <hardware/lcd_custom_characters.h>

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

void lcd1602_init(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  //Todo: Aquí se usaria la estrcutura de datos con un FOR?.
  lcd.createChar(0, resistance_up);
  lcd.createChar(1, resistance_down);
  lcd.createChar(2, resistance_rear);
  lcd.createChar(3, resistance_up_down);
  lcd.createChar(4, resistance_up_rear);
  lcd.createChar(5, resistance_down_rear);
  lcd.createChar(6, resistance_up_down_rear);
  lcd.createChar(7, bell);
  lcd.home();
}

void clear_screen(){

}

void write_screen(){

}