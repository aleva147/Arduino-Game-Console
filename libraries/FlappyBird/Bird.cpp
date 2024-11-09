#include "Bird.h"



/// Constructors:
Bird::Bird() {}
Bird::Bird(uint8_t column, uint8_t height, uint16_t speed) {
    this->column = column;
    this->height = height;
    this->initialSpeed = speed;
    this->speed = speed;
    acceleration = INIT_ACCELERATION;
}


/// Getters and Setters:
uint8_t Bird::getColumn() { return column; }
void Bird::setColunn(uint8_t column) { this->column = column; }
uint8_t Bird::getHeight() { return height; }
void Bird::setHeight(uint8_t height) { this->height = height; }
uint16_t Bird::getSpeed() { return speed; }


/// In-game logic:
void Bird::move(bool upwards) {
    if (upwards && height < ROWS_CNT-1) {
        height++;
        speed = initialSpeed;
        acceleration = INIT_ACCELERATION;
    }
    else if (!upwards) {
        height--;
        speed -= (uint16_t)(acceleration * speed);
        // Decrease bird's acceleration unless it has already reached the final value:
        if (acceleration > FINAL_ACCELERATION) acceleration -= CHANGE_ACCELERATION;
    }
}