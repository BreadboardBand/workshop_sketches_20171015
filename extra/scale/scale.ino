#include "pitches.h"
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/triangle_analogue512_int8.h> // wavetable

Oscil<TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> oscillator(TRIANGLE_ANALOGUE512_DATA);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please



// dorian
#if 0
static const uint8_t NumberOfNotes = 43;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_D2,  NOTE_DS2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_AS2, 
  NOTE_C3, NOTE_D3,  NOTE_DS3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3,
  NOTE_C4, NOTE_D4,  NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_C5, NOTE_D5,  NOTE_DS5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_AS5,
  NOTE_C6, NOTE_D6,  NOTE_DS6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_AS6,
  NOTE_C7, NOTE_D7,  NOTE_DS7, NOTE_F7, NOTE_G7, NOTE_A7, NOTE_AS7,
};
#endif

// major penta
#if 1
static const uint8_t NumberOfNotes = 36;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C1, NOTE_D1,  NOTE_E1, NOTE_G1, NOTE_A1, 
  NOTE_C2, NOTE_D2,  NOTE_E2, NOTE_G2, NOTE_A2, 
  NOTE_C3, NOTE_D3,  NOTE_E3, NOTE_G3, NOTE_A3,
  NOTE_C4, NOTE_D4,  NOTE_E4, NOTE_G4, NOTE_A4,
  NOTE_C5, NOTE_D5,  NOTE_E5, NOTE_G5, NOTE_A5,
  NOTE_C6, NOTE_D6,  NOTE_E6, NOTE_G6, NOTE_A6,
  NOTE_C7, NOTE_D7,  NOTE_E7, NOTE_G7, NOTE_A7,
};
#endif


// bass line
#if 0
static const uint8_t NumberOfNotes = 19;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_G3, NOTE_AS3,
  NOTE_C4, NOTE_G4, NOTE_AS4,
  NOTE_C5, NOTE_G5, NOTE_AS5,
  NOTE_C6, NOTE_G6, NOTE_AS6,
  NOTE_C7, NOTE_G7, NOTE_AS7,
};
#endif

// japanese
#if 0
static const uint8_t NumberOfNotes = 31;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_CS2, NOTE_F2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_CS2, NOTE_F3, NOTE_G3, NOTE_AS3, 
  NOTE_C4, NOTE_CS4, NOTE_F4, NOTE_G4, NOTE_AS4, 
  NOTE_C5, NOTE_CS5, NOTE_F5, NOTE_G5, NOTE_AS5, 
  NOTE_C6, NOTE_CS6, NOTE_F6, NOTE_G6, NOTE_AS6, 
  NOTE_C7, NOTE_CS7, NOTE_F7, NOTE_G7, NOTE_AS7, 
};
#endif

// minor blues
#if 0
static const uint8_t NumberOfNotes = 31;
static const uint16_t NoteNumbers[NumberOfNotes] =
{ 0, 
  NOTE_C2, NOTE_DS2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_AS2, 
  NOTE_C3, NOTE_DS3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_AS3, 
  NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_AS4, 
  NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_AS5, 
  NOTE_C6, NOTE_DS6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_AS6,  
};
#endif


// implementations
void setup()
{
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  oscillator.setFreq(440);
}

void loop()
{
  audioHook(); // required here
}


void updateControl()
{
  const int volume = mozziAnalogRead(1);
  const uint8_t noteIndex = map(volume, 0, 1023, 0, NumberOfNotes - 1);
  oscillator.setFreq((int)NoteNumbers[noteIndex]);
  
}

int updateAudio(){
   char sig =  (int) (oscillator.next());   
   return sig;
}

