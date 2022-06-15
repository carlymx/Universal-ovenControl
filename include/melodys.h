/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/
#include <pitches_notes.h>

#define NOTE_DURATION       1500    // ms
#define ALARM_REPETITION    4       // steps

int size_melody_array = 0;
String go_melody = "melody_01";
String go_note_duration = "note_durations_01";

//==========================================
//                FUNCTIONS                =
//==========================================

void melody(){
    int size_melody_array = sizeof(go_melody);

    for (int thisNote = 0; thisNote < size_melody_array; thisNote++) {
        tone(PIN_SPEEKER, go_melody[thisNote], (NOTE_DURATION/go_note_duration[thisNote]));
        delay (200);
    }
    return;
}

void alarm(){
    for (int i; i < ALARM_REPETITION; i++){
        tone(PIN_SPEEKER, NOTE_B6, NOTE_DURATION);
        delay (500);
    }
}


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

//========================
//=       MELODY'S       =
//========================

int melody_01[] = {         // START
NOTE_C4, NOTE_D4, NOTE_E4
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

float note_durations_99[] = { 6,6,4,6,6,4,6,6,6,6,2,6,6,6,6,6,6,6,6,6,6,6,6,2 };