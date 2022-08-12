/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/




//==================================//
//           FUNCTIONS:             //
//==================================//

void lcd_init() {
  lcd.begin();
  //Todo: Aquí se usaria la estrcutura de datos con un FOR.
  lcd.createChar(0, resistance_up);
  lcd.createChar(1, resistance_down);
  lcd.createChar(2, resistance_rear);
  lcd.createChar(3, resistance_updown);
  lcd.createChar(4, resistance_uprear);
  lcd.createChar(5, resistance_downrear);
  lcd.createChar(6, resistance_updownrear);
  lcd.createChar(7, bell);
  lcd.home();
  lcd.write(0);
}