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

bool resistance_active = false;

void set_resistance(byte resist, bool active) {
    resistance_active = active;
}
