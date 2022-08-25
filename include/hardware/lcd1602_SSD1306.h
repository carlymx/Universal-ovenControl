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

#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT    32 // OLED display height, in pixels
#define OLED_RESET       -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    
    display.display();
    delay(1000);
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