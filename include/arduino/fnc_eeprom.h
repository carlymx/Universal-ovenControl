/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

//=================================================
//           ARDUINO EEPROM FUNCTIONS:            =
//=================================================

#include <EEPROM.h>

void write_eeprom(){
    int eeprom_address = 0;
    EEPROM.put(eeprom_address, EEPROM_CRC_CONTROL);
        eeprom_address += sizeof(EEPROM_CRC_CONTROL);
    EEPROM.put(eeprom_address, PROJECT_NAME);
        eeprom_address += sizeof(PROJECT_NAME);
    EEPROM.put(eeprom_address, PROJECT_VERSION);
        eeprom_address += sizeof(PROJECT_VERSION);
    EEPROM.put(eeprom_address, PROJECT_URL);
        eeprom_address += sizeof(PROJECT_URL);
    EEPROM.put(eeprom_address, PROJECT_TEMP_IN);
        eeprom_address += sizeof(PROJECT_TEMP_IN);   
    EEPROM.put(eeprom_address, prog_eeprom_actual);
        eeprom_address += sizeof(program_eeprom);
}

void format_eeprom(){
    int eeprom_size = EEPROM.length();

    Serial.print("ERASE EEPROM...\n");
    for( int index=0; index<eeprom_size; index++){
        EEPROM[index] = 0;
    }
    delay(500); Serial.print("ERASE COMPLETE.\n");

    Serial.print("EEPROM FORMATING...\n");
    write_eeprom();
    delay(500);
    Serial.print("FORMAT COMPLETE...\n");
    delay(1000);
}

void read_eeprom(){
    init_program_eeprom(&prog_eeprom_actual);

    int eeprom_address = 0;

    int err = 0;
    int iread;
    String aux;
    //struct program_eeprom READ_EEPROM;
    EEPROM.get(eeprom_address, iread);
    eeprom_address += sizeof(EEPROM_CRC_CONTROL);
    if (iread != EEPROM_CRC_CONTROL) err = 1;

    if (err == 0) {
        EEPROM.get(eeprom_address, aux);
        eeprom_address += sizeof(PROJECT_NAME);
        if (aux != PROJECT_NAME) err = 2;
    }
    if (err == 0) {
        EEPROM.get(eeprom_address, aux);
        eeprom_address += sizeof(PROJECT_VERSION);
        if (aux != PROJECT_VERSION) err = 3;
    }
    if (err == 0) {
        EEPROM.get(eeprom_address, aux);
        eeprom_address += sizeof(PROJECT_URL);
        if (aux != PROJECT_URL) err = 4;
    }
    if (err == 0) {
        EEPROM.get(eeprom_address, aux);
        eeprom_address += sizeof(PROJECT_TEMP_IN);
        if (aux != PROJECT_TEMP_IN) err = 5;
    }

    if (err == 0) {    
        EEPROM.get(eeprom_address, prog_eeprom_actual);
    }
    //Serial.println("Leyendo Estructura EEPROM:");
    //Serial.println(BASIC_FORMAT_EEPROM.eepromCRC);
    //Serial.println(BASIC_FORMAT_EEPROM.data);
    //Serial.println(BASIC_FORMAT_EEPROM.temp_obj);
}