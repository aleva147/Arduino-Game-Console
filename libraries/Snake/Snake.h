#ifndef Snake_h
#define Snake_h

#include <Game.h>
#include "SnakeBody.h"

/// Constants:
const uint8_t SPD_SNAKE      = 250;					// Amount of ms the snake stays in one place.
const Field INITIAL_POS[2]   = { {3,1}, {11,1} };	// Initial positions of snakes when the game starts.
const uint8_t INITIAL_DIR[2] = { RIGHT, RIGHT };	// Initial directions in which the snakes will advance when the game starts.
const Field INITIAL_APPLE    = {5,5};				// Position in which the first apple will appear when the game starts.


class Snake : public Game {
public:
	/// Constructor from the parent class:
	using Game::Game;
	
private:
	/// Overriding methods from the parent class:
	void initialSetting() override;
	void playGame() override;
	bool checkForVictory() override;
	void displayResult() override;

	/// Additional methods for in-game logic:
	void detectDirection();
	bool moveSnakes();
	void generateApple();
	bool isFieldOccupied(Field field);
	bool collisionWithWall(Field newHead) const;


	/// Logic for game initialization:
	Timer timer;				 	// Timer used to redraw snakes on the screen.
	/// Logic which changes during the game:
	SnakeBody snake[2];				// Each player has his/hers snake, direction, and newDirection.
	int8_t dir[2], newDir[2];
	Field apple;
	bool eatenApple;
    bool isVictory;
};


#endif