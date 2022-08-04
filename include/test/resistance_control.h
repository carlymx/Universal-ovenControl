/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// DUMMY MODE

#define RESIST_UP      1
#define RESIST_DOWN    2
#define RESIST_REAR    4

#define MAX_OPT_RESISTANCE 7

bool resistance_active = false;

void set_resistance(byte resist, bool active) {
    resistance_active = active;
    Serial.print("Resistances " + (String)(active ? " ON!: " : "OFF!: ")
                    + (String)((resist & RESIST_UP) != 0 ? "UP " : "   ")
                    + (String)((resist & RESIST_DOWN) != 0 ? "DO " : "   ")
                    + (String)((resist & RESIST_REAR) != 0 ? "RE " : "   ") + "\n");
}