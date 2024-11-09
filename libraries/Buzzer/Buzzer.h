#ifndef Buzzer_h
#define Buzzer_h

#include <Arduino.h>
#include <Constants.h>


void playSound(uint16_t frequency, uint16_t duration);
void playMelody(const uint16_t* freqs, const uint16_t* durations, const uint16_t* breaks);


#endif