#include <Arduino.h>

//----------- CONFIGURATION: ----------
#define ADC_BITS         8
#define ADC_RATE  pow(2, ADC_BITS)

#define ANALOG_BUTTON1  A0
#define ANALOG_BUTTON2  A1
#define ANALOG_BUTTON3  A2
#define ANALOG_BUTTON4  A3

#define ANALOG_R1      680  // OHMs
#define ANALOG_R2      680
#define VOLTAGE_REF      5

float ADC_VALUE_B01 = ADC_RATE;  //1024,512...
float ADC_VALUE_B02 = (ADC_RATE(ANALOG_R1/(ANALOG_R1+ANALOG_R2)VOLTAGE_REF)/VOLTAGE_REF);


#define DELTA 10

#define TIME_UFAST_CLICK  100
#define TIME_FAST_CLICK     5
#define TIME_FULL_CLICK    50 

//----------- GLOBAL VARIBLES: ---------
byte bottons_array[4] = {ANALOG_BUTTON1, ANALOG_BUTTON2, ANALOG_BUTTON3, ANALOG_BUTTON4};
//int adc_values_array[8] = {1024, 512, 1024, 512, 1024, 512, 1024, 512};
float adc_values_array[] = {0,0,0,0,0,0,0,0};
int _analog_raw = 0;
byte botton_active = 0;

// TIMER:
unsigned long timer_counter = millis();
unsigned long last_timer = 0;
byte fast_counter = 0;
byte full_counter = 0;
bool ufast_click = false;
bool fast_click = false;
bool full_click = false;
//--------------------------------------


void serial_text(byte push_botton){
  Serial.println("Analog " +String(ANALOG_BUTTON1) +" Raw: " +String(_analog_raw) +" Botton: " +String(push_botton));
}

void read_inputs(){
  for(byte i=0; i<sizeof(bottons_array); i++){
    _analog_raw = analogRead(bottons_array[i]);
    if(_analog_raw > adc_values_array[i*2]-DELTA && botton_active == 0){
      botton_active = 1;
      serial_text(1);}
    else if(_analog_raw > (ADC_RATE/2)-DELTA && _analog_raw < (ADC_RATE/2)+DELTA && botton_active == 0){
      botton_active = 2;
      serial_text(2);}
    else if(_analog_raw < adc_values_array[i*2]-DELTA && botton_active != 0) botton_active = 0;
  }
}

void time_click() {
    unsigned long time_now = millis();

    //OVERFLOW
    if (last_timer > time_now){
        timer_counter = time_now;
    }
    last_timer = time_now;

    if (time_now >= timer_counter){
        ufast_click = true;
        fast_counter++;
        full_counter++;
        timer_counter = millis() + TIME_UFAST_CLICK;
        //OVERFLOW:
        if (timer_counter < time_now) timer_counter = 0xFFFFFFFF;
    }
    else ufast_click = false;
    if (fast_counter == TIME_FAST_CLICK){
        fast_counter = 0;
        fast_click = true;
    }
    else fast_click = false;
    if (full_counter == TIME_FULL_CLICK){
        full_counter = 0;
        full_click = true;
    }
    else full_click = false;
}

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_BUTTON1, INPUT);
  pinMode(ANALOG_BUTTON2, INPUT);
  pinMode(ANALOG_BUTTON3, INPUT);
  pinMode(ANALOG_BUTTON4, INPUT);
  Serial.println("Voltaje Ref: " +String(VOLTAGE_AREF) +"v");
  delay(100);
}

void loop() {
  time_click();

  if(ufast_click){
    read_inputs();
  }

  if(fast_click){
  }

  if(full_click){
  }

}