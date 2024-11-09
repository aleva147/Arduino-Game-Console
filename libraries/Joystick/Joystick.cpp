#include "Joystick.h"


/// Initialization:
void initializeJoysticks() {
	for (uint8_t i = 0; i < JOYSTICKS_CNT; i++) {
		pinMode(PIN_JOYSTICK_CLICK[i], INPUT);
		digitalWrite(PIN_JOYSTICK_CLICK[i], HIGH);  // Turns on the pull-up resistor.
	}
}


/// Detection of joystick's current position:
bool isJoystickPressed(uint8_t joystickId) {
	return digitalRead(PIN_JOYSTICK_CLICK[joystickId]) == LOW;
}

bool isJoystickAimed(uint8_t joystickId, int8_t direction) {
	int16_t x = analogRead(PIN_JOYSTICK_X[joystickId]);
	int16_t y = analogRead(PIN_JOYSTICK_Y[joystickId]);
	
	return (direction == UP && y > 1000) ||
		   (direction == DOWN && y < 30) ||
		   (direction == RIGHT && x > 1000) ||
		   (direction == LEFT && x < 30);
}

bool isSomeJoystickAimed(int8_t direction) {
	for (uint8_t i = 0; i < JOYSTICKS_CNT; i++) {
		if (isJoystickAimed(i, direction)) return true;
	}
	return false;
}

bool isEveryJoystickAimed(int8_t direction) {
	for (uint8_t i = 0; i < JOYSTICKS_CNT; i++) {
		if (!isJoystickAimed(i, direction)) return false;
	}
	return true;
}

bool isJoystickDiagonally(uint8_t joystickId) {
	int16_t x = analogRead(PIN_JOYSTICK_X[joystickId]);
	int16_t y = analogRead(PIN_JOYSTICK_Y[joystickId]);

	return (x < 250 || x > 780) && (y < 250 || y > 780);
}