/**/

unsigned long timer_counter_00 = millis();
unsigned long timer_counter_01 = millis();
float res_temp, log_res_temp;
float tempA1;                               // TEMPERATURE A1

void read_temp01() {
    timer_counter_01 = millis();

    if (timer_counter_01 > (timer_counter_00+5000)){    // AFTER 5 SEG (5000 MILLISEG)
    timer_counter_00 = millis();

    int tempA1_in = analogRead (A1);    // READ TERMISTOR A1
    res_temp = res_termistor * (adc_rate / (float)tempA1_in - 1.0); // TENSION TO RESISTENCE 
    log_res_temp = log(res_temp);   // LOGARITM FOR EQUATION

    // EQUIATION Steinhart-Hart (º Kelvin):
    tempA1 = (1.0 / (c1 + c2*log_res_temp + c3*log_res_temp*log_res_temp*log_res_temp));
    tempA1 = tempA1 - 273.15;   // CELSIUS

    Serial.println((String)res_temp + " - " + (String)tempA1_in + " - " + (String)tempA1);
    // Serial.println((String)tempA1_in);
    }
}