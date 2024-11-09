#include "Racket.h"


/// Initialization:
void Racket::initialize(const uint8_t length, const uint8_t speed, uint8_t position, uint8_t column) {
    this->len = length;
    this->spd = speed;
    this->pos = position;
    this->col = column;
    this->dir = IDLE;
}


/// Getters and Setters:
uint8_t Racket::getPosition() { return pos; }
void Racket::setPosition(uint8_t position) { this->pos = position; }
int8_t Racket::getDirection() { return dir; }
void Racket::setDirection(int8_t direction) { this->dir = direction; }


/// Other:
void Racket::move() {
	if (dir == UP && pos < (ROWS_CNT - len)) 
        pos++;
    else if (dir == DOWN && pos > 0) 
        pos--;
}

void Racket::draw(Display* display) {
    // Create a binary value where the length of the racket is represented by the amount of ones on the lowest digits.
	uint8_t racketBinary = (1 << len) - 1;
	// Shift the binary representation of the racket to the needed height in its column and redraw that column.
	display->drawCol(col, (racketBinary << (ROWS_CNT - len - pos)));
}