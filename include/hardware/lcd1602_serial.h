/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <hardware/lcd1602_layout.h>
#include <hardware/lcd1602_control.h>

void screen_clear();

#define RESSTR_MONITOR "Mon "

// char lines[2][LCD_LEN_LINE + 1];
char lines1[LCD_LEN_LINE + 1];
char lines2[LCD_LEN_LINE + 1];

char* lines[LCD_NUM_LINES] = {
    lines1,
    lines2
};

void screen_lines_write(){
    for(int i = 0; i < LCD_NUM_LINES; i++){
        Serial.print(i);
        Serial.print(":[");
        Serial.print(lines[i]);
        Serial.println("]");
    }   
}

void screen_resist_write() {
    if(_screen_resist > 0) 
        for(int i = 0; i < LCD_NUM_LINES; i++){
            lines[i][0] = _screen_resist + '0';
            lines[i][1] = 'R';
        }
    else {
        for(int i = 0; i < LCD_NUM_LINES; i++){
            lines[i][0] = ' ';
            lines[i][1] = ' ';
        }
    }

    screen_lines_write();
}

void screen_write_xy(int x, int y, char *msg, int len) {
    char* lin = lines[y];
    lin += x;

    memcpy(lin, msg, len);
}

void screen_init(){
    screen_clear();
}

void screen_backlight(bool active){
    Serial.print(RESSTR_MONITOR);
    Serial.print("Backlight ");
    Serial.println(boolean_to_onoff(active));
}

void screen_clear(){
    for(int i = 0; i < LCD_NUM_LINES; i++){
        memset(lines[i], ' ', LCD_LEN_LINE);
        lines[i][LCD_LEN_LINE] = 0;
    };
}
