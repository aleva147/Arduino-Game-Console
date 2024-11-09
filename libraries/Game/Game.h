#ifndef Game_h
#define Game_h

#include <Joystick.h>
#include <Display.h>
#include <Drawings.h>
#include <Buzzer.h>
#include <Melodies.h>
#include <Timer.h>

const uint16_t SPD_COUNTDOWN = 450;  // The amount of ms each digit will stay on screen during the countdown to the start of the game.


class Game {
public:
    /// Constructors:
    Game(Display* display);

    /// Starting the game:
    void startGame(uint8_t numOfPlayers);

protected:
    /// Managing the game:
    virtual void initialSetting()    = 0;
	virtual void playGame()          = 0;
	virtual bool checkForVictory()   = 0;
	virtual void endGame();
	virtual void displayResult()     = 0;

    /// Other methods:
	void countdown(uint8_t startingDigit);


    /// Logic for game initialization:
    Display* display;
	uint8_t numOfPlayers;
    /// Logic which changes during the game:
	bool gameover = false;
	bool playAgain = true;
};


#endif