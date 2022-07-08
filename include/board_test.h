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

byte test = 0;

void loop_board_test(){
    // SPEEKER PROBE
    if (test == 0){
        tone(PIN_SPEEKER, 4000, 250);
        delay (500);
        test = 1;
    }

    // RELAY TESTING
    if ( test == 1){
        tone(PIN_SPEEKER, 2000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_LIGHT_CHAMBER, 1);
            delay(250);
            digitalWrite(PIN_LIGHT_CHAMBER, 0);
            delay(250);
        }
        test = 2;
    }
    if ( test == 2){
        tone(PIN_SPEEKER, 2000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_RESISTOR_UP, 1);
            delay(250);
            digitalWrite(PIN_RESISTOR_UP, 0);
            delay(250);
        }
        test = 3;
    }
    if ( test == 3){
        tone(PIN_SPEEKER, 2000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_RESISTOR_DOWN, 1);
            delay(250);
            digitalWrite(PIN_RESISTOR_DOWN, 0);
            delay(250);
        }
        test = 4;
    }
    if ( test == 4){
        tone(PIN_SPEEKER, 2000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_RESISTOR_REAR, 1);
            delay(250);
            digitalWrite(PIN_RESISTOR_REAR, 0);
            delay(250);
        }
        test = 5;
    }
    // FAN DIMMER TESTING
    if ( test == 5){
        tone(PIN_SPEEKER, 1000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_COOL_FAN, 1);
            delay(250);
            digitalWrite(PIN_COOL_FAN, 0);
            delay(250);
        }
        test = 6;
    }   
    if ( test == 6){
        tone(PIN_SPEEKER, 1000, 500);
        delay (1000);
        for (int i=0; i<10; i++){
            digitalWrite(PIN_CHAMBER_FAN, 1);
            delay(250);
            digitalWrite(PIN_CHAMBER_FAN, 0);
            delay(250);
        }
        test = 7;
    }

    // FAN PWM PROBE
    if ( test == 7) {
        tone(PIN_SPEEKER, 500, 500);
        for (byte ii=0; ii<5; ii++){
            for (byte i=0; i<255; i=i+5){
                analogWrite(PIN_PCB_FAN, i);
                delay(20);
            }
            for (byte i=255; i>255; i=i-5){
                analogWrite(PIN_PCB_FAN, i);
                delay(20);
            }
        }
        test = 8;
    }




}