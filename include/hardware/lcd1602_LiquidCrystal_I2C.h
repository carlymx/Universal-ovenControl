/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <hardware/lcd1602_custom_char.h>
#include <hardware/lcd1602_layout.h>
#include <hardware/lcd1602_control.h>

#define ICON_RESIST         0 // RESERVED FROM 0 TO 3
#define ICON_BELL           4 

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// LCD1602 I2C [ adress: 0x27 ]
LiquidCrystal_I2C lcd(0x27,16,2);

void screen_init(){
  lcd.init();                      // initialize the lcd 
  lcd.createChar(ICON_BELL, bell);
  lcd.home();
  lcd.clear();
}

void screen_backlight(bool active){
  if (active == true) lcd.backlight();
  else lcd.noBacklight(); 
}

void screen_clear(){
  lcd.clear();
}

void screen_lines_write(){
}

void screen_resist_write() {
  if (_screen_resist == 0) {
    lcd.setCursor(LCD_POS_RES_L1_X, LCD_POS_RES_L1_Y);
    lcd.print("  ");
    lcd.setCursor(LCD_POS_RES_L2_X, LCD_POS_RES_L2_Y);
    lcd.print("  ");
  }
  else {
    byte res = (_screen_resist - 1) * 4;

    // Cargamos iconos
    for (byte i = 0; i < 4; i++)
      lcd.createChar(ICON_RESIST + i, resis_char[res + i]);

    lcd.setCursor(LCD_POS_RES_L1_X, LCD_POS_RES_L1_Y);
    lcd.printByte(ICON_RESIST);
    lcd.printByte(ICON_RESIST + 1);
    lcd.setCursor(LCD_POS_RES_L2_X, LCD_POS_RES_L2_Y);
    lcd.printByte(ICON_RESIST + 2);
    lcd.printByte(ICON_RESIST + 3);
  }
    screen_lines_write();
}

void screen_write_xy(int x, int y, char *msg, int len) {
  lcd.setCursor(x, y);
  lcd.print(msg); // TODO: len se deberia usar?
}

void screen_alarm(byte alarm){
  lcd.setCursor(13, 0);
  lcd.print(alarm);
  lcd.printByte(ICON_BELL);
}