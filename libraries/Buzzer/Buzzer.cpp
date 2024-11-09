#include "Buzzer.h"


void playSound(uint16_t frequency, uint16_t duration) {
	tone(PIN_BUZZER, frequency, duration);
}

void playMelody(const uint16_t* freqs, const uint16_t* durations, const uint16_t* breaks) {
	uint16_t notesCnt = pgm_read_word(&(freqs[0]));

    for (uint8_t note = 0; note < notesCnt; note++) {
		playSound(pgm_read_word(&(freqs[note+1])), pgm_read_word(&(durations[note])));
		delay(pgm_read_word(&(breaks[note])));
    }
}