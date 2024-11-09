#ifndef Pong_h
#define Pong_h

#include <Game.h>
#include <Racket.h>
#include <RacketBot.h>

/// Constants:
const uint8_t RACKET_LEN = 2;		// Racket length in pixels.
const uint8_t RACKET_POS = 3;		// Racket's starting height.
const uint8_t RACKET_COL[] = {0, COLS_CNT-1};	// Columns in which the rackets will placed.

const uint8_t PLAYER_SPD = 225;		// Amount of ms that needs to elapse before the player's racket can move to a new position.
const uint8_t BOT_SPD    = 110;		// Amount of ms that needs to elapse before the bot's racket can move to a new position.
 
const uint8_t BALL_SPD = 220;		// Ball's initial speed.
const uint8_t BALL_ACC = 6;			// By how much the ball will accelerate after every bounce off a racket.

const uint8_t FOR_VICTORY = 3;		// Number of points needed for victory.



class Pong : public Game {
public:
	/// Constructor from the parent class.
	using Game::Game;

private:	
	/// Overriding methods from the parent class:
	void initialSetting() override;
	void playGame() override;
	bool checkForVictory() override;
	void displayResult() override;
	
	/// Additional methods for in-game logic:
	void detectRacketDirection();
	void moveBall();
	void collisionWithRacket();
	void collisionWithWall();
	void endRound();
	void displayRoundResult();


	/// Logic for initialization:
	Timer timerPlayers, timerBall;		// Timers used to redraw the rackets controlled by players and the ball on the screen.
	Timer timerBot;						// Timer used to redraw the bot racket.

	/// Logic which changes during the game:
	bool roundOver = false;				// Game will be played over and over again until someone reaches the number of points needed for a win.
	uint8_t points[2] = {0,0};			// The number of points each player has collected so far.
	Racket* racket[2];
	Ball ball;
	uint8_t winner;						// ID of the racket which has won.
};


#endif