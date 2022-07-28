/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
// TEST MODE:

byte current_vel_cool = 0;
byte current_vel_rear = 0;

void dimmer_control_cool(byte vel) {
    if (current_vel_cool != vel) {
        current_vel_cool = vel;
        Serial.print("Dimmer Cool: "+String(vel) +" - " +String((vel*100)/255) +"%" +"\n");
    }
}


void dimmer_control_rear(byte vel) {
        if (current_vel_rear != vel) {
        current_vel_rear = vel;
        Serial.print("Dimmer Rear: "+String(vel) +" - " +String((vel*100)/255) +"%" +"\n");
    }
}
