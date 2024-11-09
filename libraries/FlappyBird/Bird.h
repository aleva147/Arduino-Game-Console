#ifndef Bird_h
#define Bird_h

#include <Constants.h>


// Initial acceleration value is big because the bird is moving very slowly before it starts to fall and we need to drastically increase its speed.
const float INIT_ACCELERATION = 0.4;
// Final acceleration value is very small because by then the bird is already being quickly redrawn on the screen and it doesn't need additional major accelerations.
const float FINAL_ACCELERATION = 0.00;
// Factor by which the acceleration will decrease as the bird falls because its speed will grow and a big acceleration won't be needed anymore. 
const float CHANGE_ACCELERATION = 0.1;


class Bird {
public:
    /// Constructors:
    Bird();
    Bird(uint8_t column, uint8_t height, uint16_t speed);

    /// Getters and Setters:
    uint8_t getColumn();
    void setColunn(uint8_t column);
    uint8_t getHeight();
    void setHeight(uint8_t height);
    uint16_t getSpeed();

    /// In-game logic:
    void move(bool upwards);

private:
    uint8_t column; 
    uint8_t height;
    // Amount of ms until the bird gets redrawn on the screen (lower value = faster bird movement).
    uint16_t initialSpeed, speed; 
    float acceleration;
};


#endif