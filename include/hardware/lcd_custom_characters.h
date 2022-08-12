/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/


// https://maxpromer.github.io/LCD-Character-Creator/
//ToDo: CREAR ESTRUCTURAS DE DATOS PARA MOSTRAR EN PANTALLA


// LCD 1602 (COLUM, FILE)
byte char_resis_a = lcd.setCursor(0,0);
byte char_resis_b = lcd.setCursor(1,0);
byte char_resis_c = lcd.setCursor(0,1);
byte char_resis_d = lcd.setCursor(1,1);

struct data_for_lcd_1602{

}
