#include "Pong.h"


/// Overriding methods from the parent class:
void Pong::initialSetting() {
	// Ball initialization:
	Field ballPos = {(uint8_t)random(COLS_CNT/2 - 1, COLS_CNT/2 + 1), 
					 (uint8_t)random(1, ROWS_CNT - 1)};	// The ball will spawn in one of the middle columns with random height.
	uint8_t ballDir = (uint8_t)random(4);	// Initial direction will become UL, UR, DL or DR.
	ball = Ball(ballPos, ballDir, BALL_SPD);
	display->changePixel(ballPos.x, ballPos.y, HIGH);
	
	// Player rackets initialization:
	for (uint8_t i = 0; i < numOfPlayers; i++) {
		racket[i] = new Racket();
		racket[i]->initialize(RACKET_LEN, PLAYER_SPD, RACKET_POS, RACKET_COL[i]);
		racket[i]->draw(display);
	}

	// Bot racket initialization: (only if this is a singleplayer game)
	if (numOfPlayers == 1) {
		RacketBot* bot = new RacketBot();
		bot->setBall(&ball);
		racket[1] = bot;
		racket[1]->initialize(RACKET_LEN, BOT_SPD, RACKET_POS, RACKET_COL[1]);
		racket[1]->draw(display);
	}

	// Timer initialization:
	timerBall = Timer();
	timerPlayers = Timer();
	if (numOfPlayers == 1) timerBot = Timer();
}

void Pong::playGame() {
	while (1) {
		detectRacketDirection();

		// Move player rackets:
		if (timerPlayers.elapsedPeriod(PLAYER_SPD)) {
			for (uint8_t i = 0; i < numOfPlayers; i++) {
				racket[i]->move();
				racket[i]->draw(display);
			}
		}
		
		// Move the bot racket if this is a singleplayer game:
		if (numOfPlayers == 1 && timerBot.elapsedPeriod(BOT_SPD)) {
			racket[1]->move();
			racket[1]->draw(display);
		}

		// Move the ball:
		if (timerBall.elapsedPeriod(ball.getSpeed())) {
			moveBall();

			// Check if the round is over:
			Field ballPos = ball.getPosition();
			if (ballPos.x == RACKET_COL[0] || ballPos.x == RACKET_COL[1]) {
				// Process the end of a round:
				endRound();
				displayRoundResult();
				delay(1500);

				// Check if the game is over:
				gameover = checkForVictory();
				if (gameover) {
					playMelody(MLD_VCT_1_FREQS, MLD_VCT_1_DURS, MLD_VCT_1_BREAKS);
					points[0] = 0;
					points[1] = 0;
				}

				// Deallocate allocated memory:
				delete racket[1];
				delete racket[0];

				return;
			}
		}
	}
}

bool Pong::checkForVictory() {
	if (points[0] == FOR_VICTORY || points[1] == FOR_VICTORY) {
		winner = (points[0] == FOR_VICTORY) ? 0 : 1;
		return true;
	}
	return false;
}

void Pong::displayResult() {
	display->drawImage(DRW_PONG_RESULT[winner], true);
}


/// Additional methods for in-game logic:
void Pong::detectRacketDirection() {
	for (uint8_t i = 0; i < numOfPlayers; i++) {
		if (isJoystickAimed(i, UP)) racket[i]->setDirection(UP);
		else if (isJoystickAimed(i, DOWN)) racket[i]->setDirection(DOWN);
		else racket[i]->setDirection(IDLE);
	}
}

void Pong::moveBall() {
	uint8_t x = ball.getPosition().x;
	uint8_t y = ball.getPosition().y;

	// Process possible collisions:
	if (y == 0 || y == ROWS_CNT-1) collisionWithWall();
	if (x == RACKET_COL[0]+1 || x == RACKET_COL[1]-1) collisionWithRacket();
	
	// Advance the ball to its new position:
	display->changePixel(x, y, LOW);
	ball.move();
	display->changePixel(ball.getPosition().x, ball.getPosition().y, HIGH);
}

void Pong::collisionWithWall() {
	uint8_t dir = ball.getDirection();

	// Collision with the top wall: (ball gets reflected downwards and keeps the same horizontal direction)
	if ((dir == UR || dir == UL) && ball.getPosition().y == ROWS_CNT-1)
		ball.setDirection(dir == UR ? DR : DL);
	// Collision with the bottom wall: (ball gets reflected upwards and keeps the same horizontal direction)
	else if ((dir == DR || dir == DL) && ball.getPosition().y == 0)
		ball.setDirection(dir == DR ? UR : UL);
}

void Pong::collisionWithRacket() {
	bool collision = false;

	uint8_t dir = ball.getDirection();
	bool left = dir == UL || dir == DL;
	bool up = dir == UL || dir == UR;
	bool down = dir == DL || dir == DR;
	uint8_t ballY = ball.getPosition().y;
	
	// If the ball is moving to the left, we are only checking for collision with the left racket. And vice versa.
	uint8_t racketPos = racket[left ? 0 : 1]->getPosition();

	// Collision with the bottom corner of the racket is allowed when the ball is moving upwards (that's why it's racketPos-1, not only racketPos).
	if (up && (racketPos-1) <= ballY && (racketPos+RACKET_LEN) > ballY) {
		// Special case: Don't allow the ball to bounce off the bottom corner of the racket if the ball is in the lowest row on the display.
		//               Now the players will have to move the rackets all the way down in this situation to block the ball.
		if (ballY == 0 && racketPos == 1) { 
			ball.setDirection(left ? L : R);		// Move to ball in-between the racket and the wall.
		}
		// Otherwise: Ball gets the opposite horizontal direction, but keeps the same vertical direction.
		else {
			ball.setDirection(dir == UL ? UR : UL);
			collision = true;
		}
	}
	// Collision with the top corner of the racket is allowed when the ball is moving downwards (that's why it's racketPos+RACKET_LEN+1).
	else if (down && racketPos <= ballY && (racketPos+RACKET_LEN+1) > ballY) {
		// Special case: Don't allow the ball to bounce off the top corner of the racket if the ball is in the highest row on the display.
		//               Now the players will have to move the rackets all the way up in this situation to block the ball.
		if (ballY == ROWS_CNT-1 && racketPos == 5) { 
			ball.setDirection(left ? L : R);		// Move to ball in-between the racket and the wall.
		}
		// Otherwise: Ball gets the opposite horizontal direction, but keeps the same vertical direction.
		else {
			ball.setDirection((dir == DL) ? DR : DL);
			collision = true;
		}
	}
	
	// In case of a collision, play the sound and accelerate the ball:
	if (collision) {		
		playSound(NOTE_D5, 60);
		// Prevents the reaching of negative ball speed.
		if (ball.getSpeed() > BALL_ACC) {
			ball.setSpeed(ball.getSpeed() - BALL_ACC);
		}
	}
}

void Pong::endRound() {
	playMelody(MLD_VCT_2_FREQS, MLD_VCT_2_DURS, MLD_VCT_2_BREAKS);
	
	delay(1000);
	
	// Point for player1:
	if (ball.getPosition().x == RACKET_COL[1]) points[0]++;
	// Point for player2:
	else if (ball.getPosition().x == RACKET_COL[0]) points[1]++;
}

void Pong::displayRoundResult() {
	// To make the display prettier when the second player has 1 point, that digit will be closer to the middle of the screen.
	uint8_t displRightDigit = points[1] == 1 ? 3 : 2;
	
	// Digits:
	uint16_t image[8];
	for (uint8_t i = 0; i < ROWS_CNT; i++) {
		image[i] = pgm_read_byte(&DRW_DIGIT[points[0]][i]) << 11;
		image[i] |= pgm_read_byte(&DRW_DIGIT[points[1]][i]) << displRightDigit;
	}
	// Colon between the two scores:
	image[2] |= 0x180;
	image[5] |= 0x180;
	
	display->drawImage(image, false);
}