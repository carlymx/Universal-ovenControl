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

byte pin_out[] = {
    PIN_LIGHT_CHAMBER, PIN_RESISTOR_UP, PIN_RESISTOR_DOWN,
    PIN_RESISTOR_REAR, PIN_COOL_FAN, PIN_CHAMBER_FAN, PIN_PCB_FAN
};

byte pin_in[] = {
    PIN_OPEN_DOOR, PIN_PUSH_00, PIN_PUSH_01,
    PIN_PUSH_02, PIN_PUSH_03, PIN_TEMP_SENSOR_01,
    PIN_TEMP_SENSOR_02    
}; 


void board_test_outputs(){
    for (byte x=0; x<sizeof(pin_out); x++){
        tone(PIN_SPEEKER, 2000, 500);
        delay (250);
        bool state = false;
        for (byte i=0; i<20; i++){
            digitalWrite(pin_out[x], state=!state);
            delay(250);
        }
    }
}

byte board_read_inputs(){
    byte res = 0;
    for (byte x=0; x<sizeof(pin_in); x++){
        if ((bool)digitalRead(pin_in[x]) == true) 
            res = res | (1 << x);               
    }
    return res;
}

void board_test_inputs_verif(int inputs){
    noTone(PIN_SPEEKER);
    if (inputs != 0){
        unsigned int var_tone = 200*(inputs);
        tone(PIN_SPEEKER, var_tone);
    }
}

//===========================================
//              EEPROM CONFIG:              =
//===========================================

/* THIS WILL ERASE THE ENTIRE CONTENT OF THE 
EEPROM (WRITE ALL 0'S) AND FORMAT IT WITH THE 
DATA REQUIRED FOR A FIRST START-UP. */
#ifdef FORMAT_EEPROM
String project_data[]={
    (String)PROJECT_NAME, (String)PROJECT_VERSION,
    (String)PROJECT_URL, (String)PROJECT_TEMP_IN};

byte temp_objective[]={
    0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75,
    80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140,
    145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200,
    205, 210, 215, 220, 225, 230, 235, 240, 245, 250};

int temp_map_empty[51]={
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0};

int temp_map00[51]={
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0};

// EEPROM STRUCTURE:
struct program_eeprom {
    byte eepromCRC;
    String* data;
    byte* temp_obj;
    bool mapped01;
    int* temp_map01;
    bool mapped02;
    int* temp_map02;
};

// OBJECT IMPLEMENTATION
struct program_eeprom BASIC_FORMAT_EEPROM = {EEPROM_CRC_CONTROL,
    project_data, temp_objective, false, temp_map_empty, false,
    temp_map_empty};


void format_eeprom(){
    int eeprom_size = EEPROM.length();
    int eeprom_address = 0;
    Serial.print("ERASE EEPROM...\n");
    for( int index=0; index<eeprom_size; index++){
        EEPROM[index] = 0;
    }
    delay(500); Serial.print("ERASE COMPLETE.\n");

    Serial.print("EEPROM FORMATING...\n");
    eeprom_address += sizeof(program_eeprom);
    EEPROM.put(eeprom_address, BASIC_FORMAT_EEPROM);
    delay(500);
    Serial.print("FORMAT COMPLETE...\n");
    delay(1000);

    struct program_eeprom READ_EEPROM;
    EEPROM.get(eeprom_address, BASIC_FORMAT_EEPROM);
    Serial.println("Leyendo Estructura EEPROM:");
    Serial.println(BASIC_FORMAT_EEPROM.eepromCRC);
    Serial.println(BASIC_FORMAT_EEPROM.data);
    Serial.println(BASIC_FORMAT_EEPROM.temp_obj);
}
#endif