#include "Timer.h"


// Note: Uses Arduino's millis() method. Doesn't support nonstop usage of microcontroller longer than 49 days.
bool Timer::elapsedPeriod(unsigned long periodMS) {
  unsigned long curMoment = millis();
  passedMS += curMoment - prevMoment;
  prevMoment = curMoment;

  if (passedMS > periodMS) {
    passedMS = 0;
    return true;
  }
  else {
    return false; 
  }
}

void Timer::reset() {
  passedMS = 0;
  prevMoment = millis();
}