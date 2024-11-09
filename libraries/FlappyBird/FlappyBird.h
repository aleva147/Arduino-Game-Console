#ifndef FlappyBird_h
#define FlappyBird_h

#include <Game.h>
#include <Bird.h>
#include <Pipe.h>


/// Constants:
const uint8_t  PIPES_SPACE = 4;			// How many empty columns there will be between the incoming pipes.
const uint8_t  PIPES_CNT   = PIPES_SPACE > COLS_CNT ? 1 : ceil(1.0*COLS_CNT/(PIPES_SPACE+1));  // Largest amount of pipes which can be on the screen simultaneously.
const uint16_t PIPES_SPD  = 264;		// Amount of ms until all the pipes get redrawn on the screen (lower value = faster pipe movement).
const uint8_t  HOLE_SIZE  = 2;		 	// Length of pipe holes in pixels.
const uint8_t  MAX_HOLE_HEIGHT = ROWS_CNT - HOLE_SIZE;	// Max possible height on the screen where a hole can start.

const uint16_t BIRD_SPD    = 735;    	// Amount of ms until the bird gets redrawn (in the moment immediately after clicking and flying up).
const uint8_t  BIRD_COL    = 7;      	// Column in which the bird will be positioned in case of a singleplayer game.
const uint8_t  BIRDS_COL[2] = {3,10}; 	// Columns in which the birds will be positioned in case of a multiplayer game.
const uint8_t  BIRD_INIT_HEIGHT  = 5;   // Height on which the birds will be positioned when the game begins.

const uint8_t  POINTS_FOR_VICT = 50;	// Number of obstacles through which the bird needs to pass in order for the player to win.


class FlappyBird : public Game {
public:
	// Constructor from the parent class.
	using Game::Game;
	
private:
	/// Overriding methods from the parent class:
	void initialSetting() override;
	void playGame() override;
	bool checkForVictory() override;
	void displayResult() override;

	/// Additional methods for in-game logic:
    void moveBird(uint8_t birdId, bool upwards);
	void movePipes();
    void collision();


	/// Logic for game initialization:
	Timer timerBird[2], timerPipes;	// Timers used to redraw birds and pipes on the screen.
    /// Logic which changes during the game:
    Bird bird[2];					// Each player will have his own bird in case of a multiplayer game.
    Pipe pipes[PIPES_CNT];			// Stores the minimal needed amount of pipes which will exist simultaneously and which will be reused throughout the game.
    uint8_t lastPipe;				// The pipe which is the furthest away from the birds.
	uint8_t points;					// Current amount of collected points.
};


#endif