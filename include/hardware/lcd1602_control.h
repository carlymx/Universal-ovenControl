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

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// LCD1602 I2C [ adress: 0x27 ]
LiquidCrystal_I2C lcd(0x27,20,4);


//==================================//
//           FUNCTIONS:             //
//==================================//

void screen_init(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  // CARGAR CARACTERES 
  //for (byte i=0; i<sizeof(resis_char); i++){
  for (byte i=0; i<28; i++){
    lcd.createChar(i, resis_char[i]);
  };
  lcd.createChar(32, bell);
  lcd.home();
}

void screen_clear(){
  lcd.clear();
}

void screen_refresh(){

}

void screen_write(String msg){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  }

void screen_text(String msg){
  lcd.setCursor(position_text[0], position_text[1]);
  lcd.print(msg);
}

void screen_resistances(byte resist){
  byte res = (resist - 1) * 4;
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res);
  lcd.printByte(res + 1);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 2);
  lcd.printByte(res + 3);
}

void screen_current_temp(int temp){
  lcd.setCursor(position_current_temp[0], position_current_temp[1]);
  lcd.print(temp);
}

void screen_backlight(bool active){
  if (active == true) lcd.backlight();
  else lcd.noBacklight(); 
}

void screen_prog_temp(int temp){
  lcd.setCursor(position_slash[0], position_slash[1]);
  lcd.print("/");
  lcd.setCursor(position_prog_temp[0], position_prog_temp[1]);
  lcd.print(temp);
}

void screen_alarm(byte alarm){
  lcd.setCursor(13, 0);
  lcd.print(alarm);
  lcd.printByte(32);
}
