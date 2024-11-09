#ifndef Melodies_h
#define Melodies_h

#include <pitches.h>
#include <avr/pgmspace.h>


// Every melody is represented by three arrays: 
//  an array of note frequencies, 
//  an array of note durations and 
//  an array of break durations between notes.
// Specially, the first element of the array which contains frequencies represents the array's length instead of a frequency.


// Turn on melody:
const uint16_t MLD_TURN_ON_FREQS[]  PROGMEM = {8, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, REST, NOTE_B3, NOTE_C4};
const uint16_t MLD_TURN_ON_DURS[]   PROGMEM = {250, 125, 125, 250, 250, 250, 250, 250};
const uint16_t MLD_TURN_ON_BREAKS[] PROGMEM = {325, 163, 163, 325, 325, 325, 325, 325};

// Victory melody 1:
const uint16_t MLD_VCT_1_FREQS[]  PROGMEM = {7, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_CS4, NOTE_G3, NOTE_CS4, NOTE_G4};
const uint16_t MLD_VCT_1_DURS[]   PROGMEM = {130, 130, 130, 230, 180, 330, 470};
const uint16_t MLD_VCT_1_BREAKS[] PROGMEM = {150, 150, 150, 270, 210, 350, 470};

// Victory melody 2:
const uint16_t MLD_VCT_2_FREQS[]  PROGMEM = {3, NOTE_D5, NOTE_D5, NOTE_D5};
const uint16_t MLD_VCT_2_DURS[]   PROGMEM = {60, 60, 60};
const uint16_t MLD_VCT_2_BREAKS[] PROGMEM = {100, 100, 0};

// Defeat melody:
const uint16_t MLD_DFT_FREQS[]  PROGMEM = {3, NOTE_AS1, NOTE_AS1, NOTE_A1};
const uint16_t MLD_DFT_DURS[]   PROGMEM = {250, 250, 600};
const uint16_t MLD_DFT_BREAKS[] PROGMEM = {350, 350, 600};

// Entrance melody 1:
const uint16_t MLD_ENT_1_FREQS[]  PROGMEM = {3, NOTE_A4, NOTE_B4, NOTE_C5};
const uint16_t MLD_ENT_1_DURS[]   PROGMEM = {150, 150, 200};
const uint16_t MLD_ENT_1_BREAKS[] PROGMEM = {150, 150, 0};

// Entrance melody 2:
const uint16_t MLD_ENT_2_FREQS[]  PROGMEM = {4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4};
const uint16_t MLD_ENT_2_DURS[]   PROGMEM = {130, 130, 130, 230};
const uint16_t MLD_ENT_2_BREAKS[] PROGMEM = {150, 150, 180, 0};

// Exit melody:
const uint16_t MLD_EXT_FREQS[]  PROGMEM = {3, NOTE_C4, NOTE_B3, NOTE_A3};
const uint16_t MLD_EXT_DURS[]   PROGMEM = {150, 150, 200};
const uint16_t MLD_EXT_BREAKS[] PROGMEM = {150, 150, 150};


#endif