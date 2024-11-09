#ifndef Timer_h
#define Timer_h

#include <Arduino.h>


// Note: Uses Arduino's millis() method. Doesn't support nonstop usage of microcontroller longer than 49 days.
class Timer {
public:
	bool elapsedPeriod(unsigned long periodMS);
	void reset();

private:
	unsigned long passedMS;
	unsigned long prevMoment;
};


#endif