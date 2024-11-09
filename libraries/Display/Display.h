/*
- The used displays are oriented in such a way that the MAX72XX drivers are on the bottom. 
  This means that the coordinate system's origin is in the bottom-left corner.
- However, LedControl library expects the origin to be in the upper-left corner instead 
  (our display is rotated 90 degrees to the left).
- Because of this, lc.setColumn method actually sets a row, and lc.setRow method sets a column.
*/

#ifndef Display_h
#define Display_h

#include <Constants.h>
#include "LedControl.h"
#include "Drawings.h"

// Speed of animations used for clearing the content of the screen.
const uint8_t SPD_VERTICAL_WIPE   = 170;
const uint8_t SPD_HORIZONTAL_WIPE = 100;


class Display {
public:
	/// Initialization:
	void initialize(uint8_t intensity);
	
	/// Adapting to the different display orientation in relation to the LedControl library source code.
	void drawRow(uint8_t displayId, uint8_t rowId, uint8_t value);
	void drawCol(uint8_t colId, uint8_t value);

	/// Drawing:
	void changePixel(uint8_t x, uint8_t y, bool status);
	// Draws an image row by row on one of the used displays.
	//  - progmem: true for predefined images from Drawings.h (FLASH memory), false otherwise (RAM memory).
	void drawImage(uint8_t displayId, uint8_t image[], bool progmem);
	// Draws an image row by row across both displays (left half of the image on the left screen, right half on the right screen).
	//  - progmem: true for predefined images from Drawings.h (FLASH memory), false otherwise (RAM memory).
	void drawImage(uint16_t image[], bool progmem);
	// Clears the contents of all displays.
	void clear();
	
	/// Animating:
	// Clears the content of the given display in the given vertical direction.
	void verticalWipe(uint8_t displayId, int8_t direction);
	// Clears the whole content in the given horizontal direction.
	void horizontalWipe(int8_t direction);

private:
	LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, DISPLAYS_CNT);
};


#endif