/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

//ToDo: CREAR ESTRUCTURAS DE DATOS PARA MOSTRAR EN PANTALLA

//      0 1 3 4 5 6 7 8 9 A B C D E F G
//    ===================================
// 0: | [ ] * * 1 8 0 / 2 0 0 * * * * * |
// 1: | [ ] * C A L E N T A N D O * * * |
//    ===================================

//=============================//
//    POSITION CHARACTERS:     //
//=============================//

// LCD 1602 (COLUM, FILE) [ lcd.setCursor(0,0) ]
byte position_resis_a[2] = {0,0};
byte position_resis_b[2] = {1,0};
byte position_resis_c[2] = {0,1};
byte position_resis_d[2] = {1,1};

byte position_current_temp[2]   = {5,0};
byte position_slash[2]          = {8,0};
byte position_prog_temp[2]      = {9,0};
byte position_text[2]           = {4,1};

byte* position_data[8] = {
    position_resis_a, position_resis_b, position_resis_c, position_resis_d,
    position_current_temp, position_slash, position_prog_temp,
    position_text };


//=============================//
//     CUSTOM CHARACTERS:      //
//=============================//
// https://maxpromer.github.io/LCD-Character-Creator/

#define RESIS_UL_R0 0
#define RESIS_UR_R0 1
#define RESIS_DL_R0 2
#define RESIS_DR_R0 3

#define RESIS_UL_R1 4
#define RESIS_UR_R1 5
#define RESIS_DL_R1 6
#define RESIS_DR_R1 7

#define RESIS_UL_R2 8 
#define RESIS_UR_R2 9
#define RESIS_DL_R2 10
#define RESIS_DR_R2 11

#define RESIS_UL_R3 12 
#define RESIS_UR_R3 13
#define RESIS_DL_R3 14
#define RESIS_DR_R3 15

#define RESIS_UL_R4 16
#define RESIS_UR_R4 17
#define RESIS_DL_R4 18
#define RESIS_DR_R4 19

#define RESIS_UL_R5 20
#define RESIS_UR_R5 21
#define RESIS_DL_R5 22
#define RESIS_DR_R5 23

#define RESIS_UL_R6 24
#define RESIS_UR_R6 25
#define RESIS_DL_R6 26
#define RESIS_DR_R6 27

byte* resis_pos[28] {
    RESIS_UL_R0, RESIS_UR_R0, RESIS_DL_R0, RESIS_DR_R0, RESIS_UL_R1,
    RESIS_UR_R1, RESIS_DL_R1, RESIS_DR_R1, RESIS_UL_R2, RESIS_UR_R2,
    RESIS_DL_R2, RESIS_DR_R2, RESIS_UL_R3, RESIS_UR_R3, RESIS_DL_R3,
    RESIS_DR_R3, RESIS_UL_R4, RESIS_UR_R4, RESIS_DL_R4, RESIS_DR_R4,
    RESIS_UL_R5, RESIS_UR_R5, RESIS_DL_R5, RESIS_DR_R5, RESIS_UL_R6,
    RESIS_UR_R6, RESIS_DL_R6, RESIS_DR_R6}

// 2X2 - RESISTANCES: (7x4 = 28 CHARACTES)
// UP -- --
byte resis_up_a[8] = {0x1F,0x19,0x10,0x00,0x00,0x00,0x00,0x00};
byte resis_up_b[8] = {0x1F,0x13,0x01,0x00,0x00,0x00,0x00,0x00};
byte resis_up_c[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte resis_up_d[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// -- DO --
byte resis_do_a[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte resis_do_b[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte resis_do_c[8] = {0x00,0x00,0x00,0x00,0x00,0x10,0x1C,0xF1};
byte resis_do_d[8] = {0x00,0x00,0x00,0x00,0x00,0x01,0x07,0xF1};
// -- -- RE
byte resis_re_a[8] = {0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x1C};
byte resis_re_b[8] = {0x00,0x00,0x00,0x00,0x10,0x10,0x08,0x07};
byte resis_re_c[8] = {0x1C,0x02,0x01,0x01,0x00,0x00,0x00,0x00};
byte resis_re_d[8] = {0x07,0x08,0x10,0x10,0x00,0x00,0x00,0x00};
// UP DO --
byte resis_updo_a[8] = {0x1F,0x19,0x10,0x00,0x00,0x00,0x00,0x00};
byte resis_updo_b[8] = {0x1F,0x13,0x01,0x00,0x00,0x00,0x00,0x00};
byte resis_updo_c[8] = {0x00,0x00,0x00,0x00,0x00,0x10,0x1C,0xF1};
byte resis_updo_d[8] = {0x00,0x00,0x00,0x00,0x00,0x01,0x07,0xF1};
// UP -- RE
byte resis_upre_a[8] = {0x1F,0x19,0x10,0x00,0x01,0x01,0x02,0x1C};
byte resis_upre_b[8] = {0x1F,0x13,0x01,0x00,0x10,0x10,0x08,0x07};
byte resis_upre_c[8] = {0x1C,0x02,0x01,0x01,0x00,0x00,0x00,0x00};
byte resis_upre_d[8] = {0x07,0x08,0x10,0x10,0x00,0x00,0x00,0x00};
// -- DO RE
byte resis_dore_a[8] = {0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x1C};
byte resis_dore_b[8] = {0x00,0x00,0x00,0x00,0x10,0x10,0x08,0x07};
byte resis_dore_c[8] = {0x1C,0x02,0x01,0x01,0x00,0x10,0x1C,0xF1};
byte resis_dore_d[8] = {0x07,0x08,0x10,0x10,0x00,0x01,0x07,0xF1};
// UP DO RE
byte resis_updore_a[8] = {0x1F,0x19,0x10,0x00,0x01,0x01,0x02,0x1C};
byte resis_updore_b[8] = {0x1F,0x13,0x01,0x00,0x10,0x10,0x08,0x07};
byte resis_updore_c[8] = {0x1C,0x02,0x01,0x01,0x00,0x10,0x1C,0xF1};
byte resis_updore_d[8] = {0x07,0x08,0x10,0x10,0x00,0x01,0x07,0xF1};

byte* resis_char[28] = {
    resis_up_a, resis_up_b, resis_up_c, resis_up_d, resis_do_a,
    resis_do_b, resis_do_c, resis_do_d, resis_re_a, resis_re_b,
    resis_re_c, resis_re_d, resis_updo_a, resis_updo_b, resis_updo_c,
    resis_updo_d, resis_upre_a, resis_upre_b, resis_upre_c,
    resis_upre_d, resis_dore_a, resis_dore_b, resis_dore_c,
    resis_dore_d, resis_updore_a, resis_updore_b, resis_updore_c,
    resis_updore_d }

//1X1 - MISC:
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};

//1X1 - RESISTANCES: 
uint8_t resistance_up[8] = {0x1F,0x11,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t resistance_down[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x1F};
uint8_t resistance_rear[8] = {0x00,0x00,0x0E,0x1B,0x0E,0x00,0x00,0x00};
uint8_t resistance_up_down[8] = {0x1F,0x11,0x00,0x00,0x00,0x00,0x0A,0x1F};
uint8_t resistance_up_rear[8] = {0x1F,0x11,0x0E,0x1B,0x0E,0x00,0x00,0x00};
uint8_t resistance_down_rear[8] = {0x00,0x00,0x0E,0x1B,0x0E,0x00,0x0A,0x1F};
uint8_t resistance_up_down_rear[8] = {0x1F,0x11,0x0E,0x1B,0x0E,0x00,0x0A,0x1F};


