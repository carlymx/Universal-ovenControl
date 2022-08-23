/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//      0 1 2 3 4 5 6 7 8 9 A B C D E F 
//    ===================================
// 0: | [ ] * * 1 8 0 / 2 0 0 * * 0 0 b |
// 1: | [ ] * C A L E N T A N D O * * * |
//    ===================================

#define LCD_POS_RES_L1_X    0
#define LCD_POS_RES_L1_Y    0
#define LCD_POS_RES_L2_X    0
#define LCD_POS_RES_L2_Y    1
#define LCD_LEN_LINE       16
#define LCD_NUM_LINES       2
#define LCD_POS_TXT_X       3 // 2 - 3
#define LCD_POS_TXT_Y       1
#define LCD_LEN_TXT        13 // 12 - 14
#define LCD_POS_INFO_X      3 // 2 - 3
#define LCD_POS_INFO_Y      0
#define LCD_LEN_INFO       13 // 12 - 14
#define LCD_POS_CTEMP_X     5
#define LCD_POS_CTEMP_Y     0
#define LCD_LEN_CTEMP       3
#define LCD_POS_PTEMP_X     9
#define LCD_POS_PTEMP_Y     0
#define LCD_LEN_PTEMP       3