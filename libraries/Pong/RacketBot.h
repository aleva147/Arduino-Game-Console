#ifndef RacketBot_h
#define RacketBot_h

#include <Racket.h>
#include <Ball.h>


class RacketBot : public Racket {
public:
    /// Overriding methods from the parent class:
    void initialize(const uint8_t len, const uint8_t spd, uint8_t pos, uint8_t col) override;
    void move() override;

    /// Getters and Setters:
    void setBall(Ball* ball);
private:
    uint8_t initialPos;
    Ball* ball;
};


#endif