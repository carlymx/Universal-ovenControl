/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <includes.h>
/*
void setup() {

  // OUTPUTS PINS
  pinMode(PIN_LIGHT_CHAMBER, OUTPUT);
  pinMode(PIN_RESISTOR_UP, OUTPUT);
  pinMode(PIN_RESISTOR_DOWN, OUTPUT);
  pinMode(PIN_RESISTOR_REAR, OUTPUT);
  pinMode(PIN_COOL_FAN, OUTPUT);
  pinMode(PIN_CHAMBER_FAN, OUTPUT);
  pinMode(PIN_PCB_FAN, OUTPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  // INPUTS PINS
  pinMode(PIN_OPEN_DOOR, INPUT);
  pinMode(PRIMARY_SENSOR, INPUT);
  pinMode(SECONDARY_SENSOR, INPUT);
  pinMode(PIN_PUSH_00, INPUT);
  pinMode(PIN_PUSH_01, INPUT);
  pinMode(PIN_PUSH_02, INPUT);
  pinMode(PIN_PUSH_03, INPUT);
  pinMode(PIN_ZERO_CROSSING, INPUT);
  //INTERRUPTIONS:
  //attachInterrupt(digitalPinToInterrupt(PIN_ZERO_CROSSING), zero_crossing, RISING);

  #ifdef USB_SERIAL_PORT
    usb_serial_init();
  #endif

  Serial.print(RESSTR_STARTING);
  Serial.print(" ");
  Serial.println(RESSTR_APP_NAME);
} */


void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode( 4, INPUT);
  pinMode(12, OUTPUT);
  
  usb_serial_init();
  Serial.print(RESSTR_STARTING);
  Serial.print(" ");
  Serial.println(RESSTR_APP_NAME);  

  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);

  Serial.println("OK");  
}

void loop()
{
/* 
  if (digitalRead(A0) == true ||
      digitalRead(A1) == true ||
      digitalRead(A2) == true ||
      digitalRead(A3) == true ||
      digitalRead(4) == true) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
  byte input = digitalRead(A0) & (digitalRead(A1) << 1) & (digitalRead(A2) << 2) & (digitalRead(A3) << 3) & (digitalRead(4) << 4);

  //Serial.println(input); */

  read_inputs();
  
  if(input_change == true){
    set_lights(current_inputs != 0);
    Serial.println(current_inputs);
    input_change = false;
  }
  delay(10); // Delay a little bit to improve simulation performance
}