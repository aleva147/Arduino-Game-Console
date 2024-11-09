#include "Snake.h"


/// Overriding methods from the parent class:
void Snake::initialSetting() {
	// Snakes initializations:
	for (uint8_t i = 0; i < numOfPlayers; i++) {
		snake[i] = SnakeBody({INITIAL_POS[i].x, INITIAL_POS[i].y});
		display->changePixel(INITIAL_POS[i].x, INITIAL_POS[i].y, HIGH);
		dir[i] = INITIAL_DIR[i];
		newDir[i] = INITIAL_DIR[i];
	}

	// Apple initialization:
	apple = INITIAL_APPLE;
	display->changePixel(apple.x, apple.y, HIGH);
	eatenApple = false;
	
	// Other:
	isVictory = false;
	timer = Timer();
}

void Snake::playGame() {
	while (1) {
		detectDirection();

		if (timer.elapsedPeriod(SPD_SNAKE) == true) {
			bool successfullyMoved = moveSnakes();

			// Check for defeat:
			if (successfullyMoved == false) {
				playMelody(MLD_DFT_FREQS, MLD_DFT_DURS, MLD_DFT_BREAKS);
				
				delay(1000);
				gameover = true;
			}
			
			// If the apple was eaten:
			if (eatenApple) {
				// Check for victory:
				if (checkForVictory() == true) {
					playMelody(MLD_VCT_1_FREQS, MLD_VCT_1_DURS, MLD_VCT_1_BREAKS);
					isVictory = true;
					gameover = true;
					delay(1000);
				}
				// Generate a new apple:
				else {
					playSound(NOTE_DS5, 60);
					delay(80);
					playSound(NOTE_FS5, 60);
					
					generateApple();
					eatenApple = false;
				}
			}

			if (gameover) return;
		}
	}
}

bool Snake::checkForVictory() {
	uint8_t totalLength = 0;
	for (uint8_t snakeId = 0; snakeId < numOfPlayers; snakeId++) {
		totalLength += snake[snakeId].getLength();
	}
	return totalLength == MAX_LENGTH;
}

void Snake::displayResult() {
	// Separating individual digits from the score:
	uint8_t length = 0;
	for (uint8_t i = 0; i < numOfPlayers; i++) length += snake[i].getLength() - 1;
	uint8_t hundred = length / 100;
	uint8_t ten = (length / 10) % 10;
	uint8_t one = length % 10;

	// Merging the score along with the image of an apple or a crown, row by row.
	uint16_t image[ROWS_CNT];
	for (uint8_t i = 0; i < ROWS_CNT; i++) {
		image[i] = (pgm_read_byte(&DRW_DIGIT[one][i]) << (hundred ? 7 : 8));
		image[i] |= (pgm_read_byte(&DRW_DIGIT[ten][i]) << (hundred ? 11 : 12));
		if (hundred) image[i] |= (pgm_read_byte(&DRW_DIGIT[hundred][i]) << 15);

		if (isVictory) image[i] |= (pgm_read_byte(&DRW_CROWN[i]) << (hundred ? 0 : 1));
		else image[i] |= (pgm_read_byte(&DRW_APPLE[i]) << (hundred ? 0 : 1));
	}

	// Drawing the created image on the screen:
	display->drawImage(image, false);
}


/// Additional methods for in-game logic:
void Snake::detectDirection() {
	for (uint8_t i = 0; i < numOfPlayers; i++) {
		// If a new direction was already given and detected, ignore new directions until the snake moves to a new position.
		if (newDir[i] != dir[i]) return;
		
		// Ignore unclear (diagonal) joystick positions.
		if (isJoystickDiagonally(i)) return;
		
		// Update the new direction, unless it's opposite to the current direction.
		if (isJoystickAimed(i, LEFT)) {
			if (dir[i] != RIGHT) newDir[i] = LEFT; 
		} 
		else if (isJoystickAimed(i, RIGHT)) {
			if (dir[i] != LEFT) newDir[i] = RIGHT; 
		} 
		else if (isJoystickAimed(i, DOWN)) {
			if (dir[i] != UP) newDir[i] = DOWN;
		} 
		else if (isJoystickAimed(i, UP)) {
			if (dir[i] != DOWN) newDir[i] = UP;
		}
	}
}

bool Snake::moveSnakes() {
	Field newHeads[2];
	
	// Update snake directions and determine the positions of their new heads: 
	//  * We can't immediately append new heads to snakes because we first need to remove their tails and check for collisions.
	for (uint8_t snakeId = 0; snakeId < numOfPlayers; snakeId++) {
		dir[snakeId] = newDir[snakeId];
		
		Field newHead = snake[snakeId].getNewHead(dir[snakeId]);
		newHeads[snakeId] = newHead;
	}
	
	// Remove each snake's tail (if it didn't eat an apple):
	//  * Must be done before collision check (so the collision check doesn't take into account the old tail position when the snake doesn't grow).
	for (uint8_t snakeId = 0; snakeId < numOfPlayers; snakeId++) { 
		if (newHeads[snakeId] == apple) {
			eatenApple = true;
			continue;
		}
		
		Field tail = snake[snakeId].removeTail();
		display->changePixel(tail.x, tail.y, LOW);	
	}

	// Check for collision between snakes themselves and for collisions with walls:
	bool collision = collisionWithWall(newHeads[0]) || isFieldOccupied(newHeads[0]);
	if (numOfPlayers == 2) {
		collision = collision || newHeads[0] == newHeads[1] ||
					collisionWithWall(newHeads[1]) || isFieldOccupied(newHeads[1]);
	}
	
	// Append new heads to snakes:
	for (uint8_t snakeId = 0; snakeId < numOfPlayers; snakeId++) { 
		snake[snakeId].appendHead(newHeads[snakeId]);
		if (!collisionWithWall(newHeads[snakeId]))
			display->changePixel(newHeads[snakeId].x, newHeads[snakeId].y, HIGH);
	}

	return !collision;
}

void Snake::generateApple() {
	uint8_t x = (uint8_t)random(16);
	uint8_t y = (uint8_t)random(8);

	// Prevents apple generation on fields which are currently occupied by the snakes.
	// The first next free field will be chosen.
	while (isFieldOccupied({x,y}) == true) {
		if (++x >= COLS_CNT) {
			x = 0;
			y = (y + 1) % ROWS_CNT; 
		}	
	}

	apple = {x, y};
	display->changePixel(apple.x, apple.y, HIGH);
}

bool Snake::isFieldOccupied(Field field) {
	return (snake[0].collisionWithBody(field) == true || 
		(numOfPlayers == 2 && snake[1].collisionWithBody(field)) == true);
}

bool Snake::collisionWithWall(Field newHead) const {
	return newHead.x < 0 || newHead.x >= COLS_CNT
	 	|| newHead.y < 0 || newHead.y >= ROWS_CNT;
}