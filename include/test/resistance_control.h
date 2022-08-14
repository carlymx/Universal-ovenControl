/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/


bool resistance_active = false;

void set_resistance(byte resist, bool active) {
    resistance_active = active;
    // ToDo: ATIVAR EL HARDWARE CORRESPONDIENTE CON digitalWrite()
    if (active == true && ((resist & RESIST_UP) != 0)) digitalWrite(PIN_RESISTOR_UP, HIGH);
    else digitalWrite(PIN_RESISTOR_UP, LOW);

    if (active == true && ((resist & RESIST_DOWN) != 0)) digitalWrite(PIN_RESISTOR_DOWN, HIGH);
    else digitalWrite(PIN_RESISTOR_DOWN, LOW);
    
    if (active == true && ((resist & RESIST_REAR) != 0)) digitalWrite(PIN_RESISTOR_REAR, HIGH);
    else digitalWrite(PIN_RESISTOR_REAR, LOW);
 
    Serial.println("Resistances " + (String)(active ? " ON!: " : "OFF!: ") + resistances_to_text(resist));
}