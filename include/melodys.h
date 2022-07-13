/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    carlymx@gmail.com
    2022
***************************************************************/

#include <pitches_notes.h>

/* NOTES DEFINITION:
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

#define NOTE_DURATION   1500    // ms
#define NOTE_SILENCE     250    // ms

int melody_01[] = {         // START
    NOTE_C7, NOTE_D7, NOTE_E7, NOTE_E7, NOTE_D7, NOTE_C7
}; 

int melody_02[] = {         // ALARM!!!
    NOTE_B7, NOTE_B7
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

float note_durations_01[] = { 6,6,4,4,6,6 };

float note_durations_02[] = { 4,4 };

float note_durations_99[] = { 6,6,4,6,6,4,6,6,6,6,2,6,6,6,6,6,6,6,6,6,6,6,6,2 };


//========================
//=    STRUCTURES        =
//========================

struct melody {
    int delay;
    int numnotes;
    int* notes;
    float* duration;
};

// OBJECT IMPLEMENTATION (MELODIES)
struct melody EMPTY_MELODY = {NOTE_SILENCE, 0};
struct melody START_MELODY = {NOTE_SILENCE, 6, melody_01, note_durations_01};
struct melody ALARM_MELODY = {NOTE_SILENCE, 2, melody_02, note_durations_02};
struct melody JBELLS_MELODY = {NOTE_SILENCE, 24, melody_99, note_durations_99};

// struct melody* MELODIES[] = { START_MELODY, ALARM_MELODY };
// start_melody(MELODIES[1]);

//==========================================
//                FUNCTIONS                =
//==========================================

// PRIVATE VARS
#define NO_PLAYING_MELODY 0xffffffff

struct melody* _current_melody = &EMPTY_MELODY;
int _current_idx = 0;
unsigned long _timer_melody = NO_PLAYING_MELODY;

void start_melody(struct melody* melodiaasonar){
    // Solamente tocamos si no hay una en marcha
    if (_timer_melody == NO_PLAYING_MELODY){
        _timer_melody = millis();
        _current_idx = 0;
        _current_melody = melodiaasonar;
    }
};

void process_sound(){
    if (_timer_melody < millis()){
        if (_current_idx < _current_melody->numnotes){
            tone(PIN_SPEAKER, _current_melody->notes[_current_idx], (NOTE_DURATION/_current_melody->duration[_current_idx]));
            _timer_melody = millis() + _current_melody->delay;
            _current_idx++;
        }
        else
            _timer_melody = NO_PLAYING_MELODY;
    }
};