#include "Game.h"


/// Constructors:
Game::Game(Display* display) {
	this->display = display;
}


/// Starting the game:
void Game::startGame(uint8_t numOfPlayers) {
    this->numOfPlayers = numOfPlayers;
	
	while (playAgain == true) {
		gameover = false;
		
        while (gameover == false) {
            // Countdown to the beginning of the game:
            countdown(3);
            
            // Game initialization:
            initialSetting();
            
            // Manage game until its over:
            playGame();
        }

        // Display the result and wait for user input:
        endGame();
	}
}


/// Managing the game:
void Game::endGame() {
	displayResult();
	
	delay(1200);	// Prevents users from accidentally exiting or starting a new game immediately after seeing the result.

	// Waits for users to start a new game or to return to the main menu:
	while (1) {
		if (isSomeJoystickAimed(RIGHT)) {
			display->clear();
			playAgain = true;
			return;
		}
		else if (isSomeJoystickAimed(LEFT)) {
			playAgain = false;
			return;			
		}
	}
}

/// Other methods:
void Game::countdown(uint8_t startingDigit) {
	for (uint8_t digit = startingDigit; digit > 0; digit--) {
		for (uint8_t i = 0; i < ROWS_CNT; i++) {
			// The first two columns of the digit are drawn on the last two columns of the left screen. 
		  	display->drawRow(0, i, pgm_read_byte(&DRW_DIGIT[digit][i]) >> 1);
			// The third column of the digit is drawn on the first column of the right screen.
		  	display->drawRow(1, i, pgm_read_byte(&DRW_DIGIT[digit][i]) << 7);
		}
		
		playSound(NOTE_E3, SPD_COUNTDOWN / 2);
		delay(SPD_COUNTDOWN);
	}
	
	display->clear();
	
	playSound(NOTE_D4, SPD_COUNTDOWN);
}