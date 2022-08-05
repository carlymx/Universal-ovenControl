/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

// NORMAL MODE:

bool cool_active = false;
bool rear_active = false;
unsigned int current_vel_cool = 0;
unsigned int current_vel_rear = 0;

bool dimmer_control_power(byte pin, unsigned int vel, bool active){
    // [ ] ToDo: Control por micro segundos de los ventiladores
    // [-] ToDo: Llamar desde el bucle principal siempre que este en activo.

    if(vel == DIMMER_CONTROL_POWER_100) {
        if(active == false) {
            digitalWrite(pin, HIGH);
            active = true;
        }
    }
    else if(vel == DIMMER_CONTROL_POWER_0) {
        if(active == true) {
            digitalWrite(pin, LOW);
            active = false;
        }
    }
    else {    
        unsigned long micros_now = micros();

        if(active == true) {
            // Desactivamos cuando pasa por 0? - SI.
            if(micros_now >= next_zero) {
                digitalWrite(pin, LOW); 
                active = false;
                next_zero += DIMMER_CONTROL_POWER_100;
            }
        }
        else {
            if(micros_now >= next_zero - vel){
                digitalWrite(pin, HIGH);
                active = true;
            }
        }
    }

    return active;
}

void dimmer_control_fans(){
    cool_active = dimmer_control_power(PIN_COOL_FAN, current_vel_cool, cool_active);
    rear_active = dimmer_control_power(PIN_CHAMBER_FAN, current_vel_rear, rear_active);
}

void set_dimmer_control_cool(unsigned int vel) {
/*    if (vel == 0){          // ALARM MODE
        digitalWrite(PIN_COOL_FAN, LOW);
    } */
 
    if (current_vel_cool != vel) {
        current_vel_cool = vel;
        Serial.print("Dimmer Cool: "+String(vel) +" - " +String(vel/(10000/(AC_HERTZ*2))) +"%" +"\n");
    }
}

void set_dimmer_control_rear(unsigned int vel) {
        if (current_vel_rear != vel) {
        current_vel_rear = vel;
        Serial.print("Dimmer Rear: "+String(vel) +" - " +String(vel/(10000/(AC_HERTZ*2))) +"%" +"\n");
    }
}
