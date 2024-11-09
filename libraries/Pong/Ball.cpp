#include "Ball.h"


/// Constructors:
Ball::Ball() {}
Ball::Ball(Field position, uint8_t direction, uint8_t speed) {
    this->pos = position;
    this->dir = direction;
    this->spd = speed;
}


/// Getters and Setters:
void Ball::setDirection(uint8_t direction) { this->dir = direction; }
uint8_t Ball::getDirection() { return dir; }
void Ball::setSpeed(uint8_t speed) { this->spd = speed; }
uint8_t Ball::getSpeed() { return spd; }
Field& Ball::getPosition() { return pos; }


/// Other:
void Ball::move() {
	if (dir == UL) pos      = {pos.x - 1, pos.y + 1};
	else if (dir == UR) pos = {pos.x + 1, pos.y + 1};
	else if (dir == DL) pos = {pos.x - 1, pos.y - 1};
	else if (dir == DR) pos = {pos.x + 1, pos.y - 1};
    else if (dir == L) pos.x = pos.x - 1;
    else if (dir == R) pos.x = pos.x + 1;
}