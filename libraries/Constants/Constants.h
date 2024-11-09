#ifndef Constants_h
#define Constants_h

#include <stdint.h>


/// Physical constants:
// Joystick:
const uint8_t JOYSTICKS_CNT = 2;  // Number of joysticks used.
// Display:
const uint8_t DISPLAYS_CNT  = 2;  // Number of matrix displays used.
const uint8_t COLS_CNT_1    = 8;  // How many columns a single matrix display has.
const uint8_t COLS_CNT      = 16; // How many columns there are in total.
const uint8_t ROWS_CNT      = 8;  // How many rows a single matrix display has, but also how many rows there are in total.


/// Used microcontroller pins:
// Joystick:
const uint8_t PIN_JOYSTICK_X[JOYSTICKS_CNT]     = {19, 17};	// Player1: A5 (=19), Player2: A3 (=17).
const uint8_t PIN_JOYSTICK_Y[JOYSTICKS_CNT]     = {18, 16};	// Player1: A4 (=18), Player2: A2 (=16).
const uint8_t PIN_JOYSTICK_CLICK[JOYSTICKS_CNT] = {2, 3};   // Player1: 2, Player2: 3.
// Display:
const uint8_t PIN_DIN = 12;
const uint8_t PIN_CLK = 11;
const uint8_t PIN_CS  = 10;
// Buzzer:
const uint8_t PIN_BUZZER = 8; 


/// Logical constants:
const int8_t UP = 1, DOWN = -1, IDLE = 0, RIGHT = 2, LEFT = -2;
const uint8_t NUM_OF_GAMES = 3;


#endif