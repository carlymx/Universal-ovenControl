/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/


// https://maxpromer.github.io/LCD-Character-Creator/
//ToDo: Crear una Estructura de Datos.

uint8_t resistance_up[8] = {0x1F,0x11,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t resistance_down[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x1F};
uint8_t resistance_rear[8] = {0x00,0x00,0x0E,0x1B,0x0E,0x00,0x00,0x00};
uint8_t resistance_updown[8] = {0x1F,0x11,0x00,0x00,0x00,0x00,0x0A,0x1F};
uint8_t resistance_uprear[8] = {0x1F,0x11,0x0E,0x1B,0x0E,0x00,0x00,0x00};
uint8_t resistance_downrear[8] = {0x00,0x00,0x0E,0x1B,0x0E,0x00,0x0A,0x1F};
uint8_t resistance_updownrear[8] = {0x1F,0x11,0x0E,0x1B,0x0E,0x00,0x0A,0x1F};

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
  lcd.home();
  lcd.write(0);
}