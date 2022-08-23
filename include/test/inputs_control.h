/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

void read_inputs() {
    //byte new_inputs = current_inputs;
    byte new_inputs = 0;
     
    if (new_inputs != current_inputs) {
        current_inputs = new_inputs;
        input_change = true;
    }
}