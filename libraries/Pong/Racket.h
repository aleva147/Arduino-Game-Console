#ifndef Racket_h
#define Racket_h

#include <Constants.h>
#include <Display.h>


class Racket {
public:
    /// Initialization:
    virtual void initialize(const uint8_t length, const uint8_t speed, uint8_t position, uint8_t column);

    /// Getters and Setters:
    uint8_t getPosition();
    void setPosition(uint8_t position);
    int8_t getDirection();
    void setDirection(int8_t direction);

    /// Other:
    virtual void move();
    void draw(Display* display);

protected:
    /// Constants:
    uint8_t len;        // Racket length in pixels.
	uint8_t spd;        // Racket speed.
    uint8_t col;        // The column in which the racket will stay during the game.
    /// Variables:
	uint8_t pos;	    // Current position of the lowest point of the racket.
	int8_t dir; 		// Current racket direction.
};


#endif