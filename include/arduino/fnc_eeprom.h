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
/*    EEPROM.put(eeprom_address, PROJECT_NAME);
        eeprom_address += sizeof(PROJECT_NAME);
    EEPROM.put(eeprom_address, PROJECT_VERSION);
        eeprom_address += sizeof(PROJECT_VERSION);
    EEPROM.put(eeprom_address, PROJECT_URL);
        eeprom_address += sizeof(PROJECT_URL);
    EEPROM.put(eeprom_address, PROJECT_TEMP_IN);
        eeprom_address += sizeof(PROJECT_TEMP_IN);   */
    EEPROM.put(eeprom_address, prog_eeprom_actual);
        eeprom_address += sizeof(program_eeprom);
}

void format_eeprom(){
    int eeprom_size = EEPROM.length();
    #ifdef DEBUG_LOG
    Serial.println("ERASE EEPROM...");
    #endif
    for( int index=0; index<eeprom_size; index++){
        EEPROM[index] = 0;
    }
    delay(500); 
    #ifdef DEBUG_LOG
    Serial.println("ERASE COMPLETE.");
    Serial.println("EEPROM FORMATING...");
    #endif
    write_eeprom();
    delay(500);
    #ifdef DEBUG_LOG
    Serial.println("FORMAT COMPLETE...");
    #endif
    delay(1000);
}

int read_eeprom(){
    init_program_eeprom(&prog_eeprom_actual);

    int eeprom_address = 0;

    int err = 0;
    byte bread;
    String aux;
    //struct program_eeprom READ_EEPROM;
    EEPROM.get(eeprom_address, bread);
    eeprom_address += sizeof(EEPROM_CRC_CONTROL);
    if (bread != EEPROM_CRC_CONTROL) err = 1;

/*    if (err == 0) {
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
    } */

    #ifdef DEBUG_LOG
    Serial.print("EEPROM Err: ");
    Serial.println(err);
    #endif

    if (err == 0)
        EEPROM.get(eeprom_address, prog_eeprom_actual);

    #ifdef DEBUG_LOG
    Serial.print("Eeprom: ");
    Serial.println(prog_eeprom_actual.mapped01);
    //Serial.println("Leyendo Estructura EEPROM:");
    //Serial.println(BASIC_FORMAT_EEPROM.eepromCRC);
    //Serial.println(BASIC_FORMAT_EEPROM.data);
    //Serial.println(BASIC_FORMAT_EEPROM.temp_obj);
    #endif

    return err;
}