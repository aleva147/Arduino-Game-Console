#include "RacketBot.h"


/// Overriding methods from the parent class:
void RacketBot::initialize(const uint8_t len, const uint8_t spd, uint8_t pos, uint8_t col) {
    Racket::initialize(len, spd, pos, col);

    initialPos = pos;
}

void RacketBot::move() {
    // When the ball moves towards him, the bot follows it.
    if (ball->getDirection() == UR || ball->getDirection() == DR) {
        if (ball->getPosition().y < pos) pos--;
        else if (ball->getPosition().y > pos+(len-1)) pos++;
    }
    // When the ball moves away from him, the bot returns to his initial position in the middle of the screen.
    else {
        if (pos > initialPos) pos--;
        else if (pos < initialPos) pos++;
    }
}


/// Getters and Setters:
void RacketBot::setBall(Ball* ball) { this->ball = ball; }