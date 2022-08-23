/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

#include <hardware/lcd1602_layout.h>
#include <hardware/lcd1602_control.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// this is the Width and Height of Display which is 128 xy 32 
#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  128 

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void screen_clear();

// char lines[2][LCD_LEN_LINE + 1];
char lines1[LCD_LEN_LINE + 1];
char lines2[LCD_LEN_LINE + 1];

char* lines[LCD_NUM_LINES] = {
    lines1,
    lines2
};

#ifdef DEBUG_LOG
void screen_lines_log(){
    for(int i = 0; i < LCD_NUM_LINES; i++){
        Serial.print(i);
        Serial.print(":[");
        Serial.print(lines[i]);
        Serial.println("]");
    }   
}
#endif

void screen_lines_write(){
    #ifdef DEBUG_LOG
    Serial.print(1);
    delay(200);
    #endif

    display.clearDisplay();

    #ifdef DEBUG_LOG
    Serial.print(2);
    delay(200);
    #endif

    display.setTextSize(3);
    display.setTextColor(WHITE);

    #ifdef DEBUG_LOG
    Serial.print(3);
    delay(200);
    #endif

    for(int i = 0; i < LCD_NUM_LINES; i++){  
        display.setCursor(4, 3 + i * 8);
    #ifdef DEBUG_LOG
    Serial.print("a");
    delay(200);
    #endif
        display.println(String(lines[i]));
    #ifdef DEBUG_LOG
    Serial.print("b");
    delay(200);
    #endif
    }   

    #ifdef DEBUG_LOG
    Serial.print(4);
    delay(200);
    #endif

    //display.drawRect(1, 1, 126,31, WHITE);
    #ifdef DEBUG_LOG
    Serial.print(5);
    delay(200);
    #endif
    display.display();

    #ifdef DEBUG_LOG
    Serial.println(6);
    delay(200);
    #endif
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
    #ifdef DEBUG_LOG
    Serial.println(msg);
    delay(200);
    #endif

    char* lin = lines[y];
    lin += x;

    memcpy(lin, msg, len);

    #ifdef DEBUG_LOG
    screen_lines_log();
    delay(500);
    #endif
}

void screen_init(){   
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    display.display();
    screen_clear();
}

void screen_backlight(bool active){
    // No tiene
}

void screen_clear(){
    for(int i = 0; i < LCD_NUM_LINES; i++){
        memset(lines[i], ' ', LCD_LEN_LINE);
        lines[i][LCD_LEN_LINE] = 0;
    };

    display.clearDisplay();
}