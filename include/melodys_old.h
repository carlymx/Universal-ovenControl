/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/
#include <pitches_notes.h>

//==========================================
//                FUNCTIONS                =
//==========================================

void melody(String xx, String yy){
    byte size_melody_array = sizeof(xx);

    for (int thisNote = 0; thisNote < size_melody_array; thisNote++) {
        tone(PIN_SPEEKER, xx[thisNote], (1500/yy[thisNote]));
        delay (200);
    }
    return;
}


//========================
//=       MELODY'S       =
//========================
/*
#define NOTE_C4  262  //DO
#define NOTE_CS4 277  //DO SOSTENIDO
#define NOTE_D4  294  //RE
#define NOTE_DS4 311  //RE SOSTENIDO
#define NOTE_E4  330  //MI
#define NOTE_F4  349  //FA
#define NOTE_FS4 370  //FA SOSTENIDO
#define NOTE_G4  392  //SOL
#define NOTE_GS4 415  //SOL SOSTENIDO
#define NOTE_A4  440  //LA
#define NOTE_AS4 466  //LA SOSTENIDO
#define NOTE_B4  494  //SI
*/

int melody_01[] = {         // START
    NOTE_C4, NOTE_D4, NOTE_E4
}; 

int melody_02[] = {         // ALARM!!!
    NOTE_B4, NOTE_B4
}; 

int melody_99[] = {         // JIMBLE BELLS
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
    NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_F4,
    NOTE_D4, NOTE_C4
};


//========================
//=    NOTE DURATION     =
//========================
// time divisor: (NOTE_DURATION/[ARRAY_VALOR]) 
// durations: 2 = half note, and 8/3, 4, 6, 8, 12. 
// It appears that 8/2.9 is more accurate than 8/3.

float note_durations_01[] = { 6,6,4 };

float note_durations_02[] = { 4,4 };

float note_durations_99[] = { 6,6,4,6,6,4,6,6,6,6,2,6,6,6,6,6,6,6,6,6,6,6,6,2 };