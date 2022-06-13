/*****

*/

// ANALOG DIGITAL CONVERTER bits:
int adc_bits = 10;                               // 10 bits ARDUINO UNO,MINI, MEGA...
int adc_rate = (pow(2, adc_bits) - 1);            // 10 bits = 1023, 12 = 4095...

// THERMISTOR CONF:
float res_termistor = 100000;                   // 100KOhms

// coefficients Steinhart-Hart:
// https://tinyurl.com/SHH-Calculator
float c1 = 2.114990448e-03;                     // NPC 100KOhms
float c2 = 0.3832381228e-04;                    // NPC 100KOhms
float c3 = 5.228061052e-07;                     // NPC 100KOhms