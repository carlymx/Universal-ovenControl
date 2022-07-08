/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

//===========================================
//              BOARD TESTING:              =
//===========================================

byte m = 0;

void loop_board_test(){
    // SPEEKER PROBE
    if (m == 0){
        for (int i=0; i<3; i++){
            tone(PIN_SPEEKER, 4186, 500);
            delay (1000);
        }
        m = 1;
    }
}