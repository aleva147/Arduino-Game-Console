#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>
#include <Constants.h>


/// Initialization:
void initializeJoysticks();

/// Detection of joystick's current position:
// Checks whether the selected joystick is currently being pressed.
bool isJoystickPressed(uint8_t joystickId);
// Checks if the the selected joystick is currently being aimed in the given direction (LEFT, RIGHT, UP or DOWN). 
bool isJoystickAimed(uint8_t joystickId, int8_t direction);
bool isSomeJoystickAimed(int8_t direction);
bool isEveryJoystickAimed(int8_t direction);
// Used for ignoring unclear joystick positions while playing games with only four possible directions.
bool isJoystickDiagonally(uint8_t joystickId);


#endif