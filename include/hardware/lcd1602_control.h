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
  //for (byte i=0; i<sizeof(resis_char); i++){ // ASÍ ME DA UN PROBLEMA QUE NO CONOZCO AL COMPILAR.
  for (byte i=0; i<28; i++){
    lcd.createChar(i, resis_char[i]);
  };
  lcd.createChar(32, bell);
  lcd.home();
}

void screen_clear(){

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
  byte res = resist * 4;
  // UP -- --
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res);
  lcd.printByte(res + 1);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 2);
  lcd.printByte(res + 3);
  // -- DO --
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 4);
  lcd.printByte(res + 5);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 6);
  lcd.printByte(res + 7);
  // -- -- RE
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 8);
  lcd.printByte(res + 9);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 10);
  lcd.printByte(res + 11);
  // UP DO --
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 12);
  lcd.printByte(res + 13);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 14);
  lcd.printByte(res + 15);
  // UP -- RE
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 16);
  lcd.printByte(res + 17);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 18);
  lcd.printByte(res + 19);
  // -- DO RE
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 20);
  lcd.printByte(res + 21);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 22);
  lcd.printByte(res + 23);
  // UP DO RE
  lcd.setCursor(position_resis_a[0], position_resis_a[1]);
  lcd.printByte(res + 24);
  lcd.printByte(res + 25);
  lcd.setCursor(position_resis_c[0], position_resis_c[1]);
  lcd.printByte(res + 26);
  lcd.printByte(res + 27);
}

void screen_current_temp(int temp){

}

void screen_backlight(bool active){
  if (active == true) lcd.backlight();
  else lcd.noBacklight(); 
}

void screen_prog_temp(int temp){

}

void screen_alarm(byte alarm){
  lcd.setCursor(13, 0);
  lcd.print(alarm);
  lcd.printByte(32);
}
