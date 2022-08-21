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

//      0 1 3 4 5 6 7 8 9 A B C D E F G
//    ===================================
// 0: | [ ] * * 1 8 0 / 2 0 0 * * 0 0 b |
// 1: | [ ] * C A L E N T A N D O * * * |
//    ===================================

#define LCD_POS_RES_L1_X    0
#define LCD_POS_RES_L1_Y    0
#define LCD_POS_RES_L2_X    0
#define LCD_POS_RES_L2_Y    1
#define LCD_POS_TXT_X       4
#define LCD_POS_TXT_Y       1
#define LCD_POS_TXT_LEN    13
#define LCD_POS_CTEMP_X     5
#define LCD_POS_CTEMP_Y     0
#define LCD_POS_CTEMP_LEN   3
#define LCD_POS_PTEMP_X     9
#define LCD_POS_PTEMP_Y     0
#define LCD_POS_PTEMP_LEN   3

#define ICON_RESIST         0 // RESERVED FROM 0 TO 3
#define ICON_BELL           4 

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// LCD1602 I2C [ adress: 0x27 ]
LiquidCrystal_I2C lcd(0x27,16,2);

String _screen_text = "";
byte _screen_index = 0;
byte _screen_index_zero = 0;
String _screen_info = "";
byte _screen_info_index = 0;
byte _screen_info_index_zero = 0;
byte _screen_resist = 0;
int _screen_current_temp = 0;
int _screen_prog_temp = 0;

//==================================//
//           FUNCTIONS:             //
//==================================//

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

void screen_refresh(){
  if(_screen_text.length() > LCD_POS_TXT_LEN) {
    _screen_index_zero++;
    if (_screen_index_zero > 2){
      _screen_index++;
      if (_screen_text.length() - _screen_index + 1 < LCD_POS_TXT_LEN) {
        _screen_index = 0;
        _screen_index_zero = 0;
      }

      lcd.setCursor(LCD_POS_TXT_X, LCD_POS_TXT_Y);
      lcd.print(_screen_text.substring(_screen_index));
    }
  }
}

void screen_write(byte x, byte y, String msg){
  lcd.setCursor(x, y);
  lcd.print(msg);
}

void screen_text(String msg){
  _screen_text = msg;
  _screen_index = 0;
  _screen_index_zero = 0;

  lcd.setCursor(LCD_POS_TXT_X, LCD_POS_TXT_Y);
  lcd.print(msg);
  lcd.print("         ");
}

void screen_info(String msg){
  _screen_info = msg;
  _screen_info_index = 0;
  _screen_info_index_zero = 0;

  lcd.setCursor(LCD_POS_TXT_X, 0);
  lcd.print(msg);
  lcd.print("         ");
}

void screen_resistances(byte resist){
  _screen_resist = resist;

  if (resist == 0) {
    lcd.setCursor(LCD_POS_RES_L1_X, LCD_POS_RES_L1_Y);
    lcd.print("  ");
    lcd.setCursor(LCD_POS_RES_L2_X, LCD_POS_RES_L2_Y);
    lcd.print("  ");
  }
  else {
    byte res = (resist - 1) * 4;

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
}

void screen_print_temp(int ctemp, int ptemp){
  char buff[9];

  if(ptemp != 0)
    sprintf(buff, "%3d/%3d%s", ctemp, ptemp, " C");
  else 
    sprintf(buff, "    %3d%s", ctemp, " C");

  lcd.setCursor(LCD_POS_CTEMP_X, LCD_POS_CTEMP_Y);
  lcd.print(String(buff));
}

void screen_current_temp(int temp){
  _screen_current_temp = temp;
  screen_print_temp(temp, _screen_prog_temp);
}

void screen_prog_temp(int temp){
  _screen_prog_temp = temp;
  screen_print_temp(_screen_current_temp, temp);
}

void screen_alarm(byte alarm){
  lcd.setCursor(13, 0);
  lcd.print(alarm);
  lcd.printByte(ICON_BELL);
}