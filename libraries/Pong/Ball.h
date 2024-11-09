#ifndef Ball_h
#define Ball_h

#include <Field.h>


/// Possible ball directions: (upwards left, upwards right, left, right, downwards left, downwards right)
const uint8_t UL = 0, UR = 1,
               L = 4,  R = 5,
			  DL = 2, DR = 3;


class Ball {
public:
    /// Constructors:
    Ball();
    Ball(Field position, uint8_t direction, uint8_t speed);

    /// Getters and Setters:
    void setDirection(uint8_t direction);
    uint8_t getDirection();
    void setSpeed(uint8_t speed);
    uint8_t getSpeed();
    Field& getPosition();

    /// Other:
    void move();

private:
	Field pos;      // Current position.
	uint8_t dir;    // Current direction.
	uint8_t spd;    // Current speed.
};



#endif