#include "Display.h"


/// Initialization:
void Display::initialize(uint8_t intensity) {
	for (uint8_t i = 0; i < DISPLAYS_CNT; i++) {
		lc.shutdown(i, false);
		lc.setIntensity(i, intensity);
		lc.clearDisplay(i);  
	}
}


/// Adapting to the different display orientation in relation to the LedControl library source code.
void Display::drawRow(uint8_t displayId, uint8_t rowId, uint8_t value) {
	lc.setColumn(displayId, (ROWS_CNT-1)-rowId, value);
}

void Display::drawCol(uint8_t idCol, uint8_t value) {
	uint8_t displayId = idCol / COLS_CNT_1;
	lc.setRow(displayId, idCol % COLS_CNT_1, value);
}


/// Drawing:
void Display::changePixel(uint8_t x, uint8_t y, bool status) {
	uint8_t displayId = x / COLS_CNT_1;
	lc.setLed(displayId, x % COLS_CNT_1, y, status);
}

// Draws an image row by row on one of the used displays.
//  - progmem: true for predefined images from Drawings.h (FLASH memory), false otherwise (RAM memory).
void Display::drawImage(uint8_t displayId, uint8_t image[], bool progmem) {
	for (uint8_t i = 0; i < ROWS_CNT; i++) {
		uint8_t imageRow = progmem ? pgm_read_byte(&image[i]) : image[i];
		drawRow(displayId, i, imageRow);
	}
}

// Draws an image row by row across both displays (left half of the image on the left screen, right half on the right screen).
//  - progmem: true for predefined images from Drawings.h (FLASH memory), false otherwise (RAM memory).
void Display::drawImage(uint16_t image[], bool progmem) {
	for (uint8_t i = 0; i < ROWS_CNT; i++) {
		uint16_t imageRow = progmem ? pgm_read_word(&image[i]) : image[i];
		drawRow(0, i, imageRow >> 8);
		drawRow(1, i, imageRow & 0x00FF);
	}
}

// Clears the contents of all displays.
void Display::clear() {
	for (uint8_t i = 0; i < DISPLAYS_CNT; i++) {
		lc.clearDisplay(i);
	}
}


/// Animating:
// Clears the content of the given display in the given vertical direction.
void Display::verticalWipe(uint8_t displayId, int8_t direction) {
	for (uint8_t i = 0; i < ROWS_CNT; i++) {
		drawRow(displayId, (direction == DOWN ? i : 7-i), 0xFF);
		delay(SPD_VERTICAL_WIPE);
		drawRow(displayId, (direction == DOWN ? i : 7-i), 0x00);
	}
}

// Clears the whole content in the given horizontal direction.
void Display::horizontalWipe(int8_t direction) {
	for (uint8_t i = 0; i < COLS_CNT; i++) {
		drawCol((direction == RIGHT ? i : COLS_CNT-1-i), 0xFF);
		delay(SPD_HORIZONTAL_WIPE);
		drawCol((direction == RIGHT ? i : COLS_CNT-1-i), 0x00);
	}
	delay(2 * SPD_HORIZONTAL_WIPE);
}