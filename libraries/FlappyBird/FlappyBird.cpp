#include "FlappyBird.h"


/// Overriding methods from the parent class:
void FlappyBird::initialSetting() {
    // Generating birds:
    for (uint8_t i = 0; i < numOfPlayers; i++) {
        bird[i] = Bird(numOfPlayers == 1 ? BIRD_COL : BIRDS_COL[i], BIRD_INIT_HEIGHT, BIRD_SPD);
        display->changePixel(bird[i].getColumn(), bird[i].getHeight(), HIGH);
    }

    // Generating pipes: (the minimal amount of pipe objects needed throughout the game is generated now even though the pipes won't yet be visible).
    pipes[0].column = COLS_CNT + 2;  // First pipe is initially positioned two columns behind the screen's last column.
    pipes[0].holeHeight = random(MAX_HOLE_HEIGHT+1);
    lastPipe = 0;
    for (uint8_t i = 1; i < PIPES_CNT; i++) {
        pipes[i].column = pipes[lastPipe].column + PIPES_SPACE+1;

        // Prevent neighboring pipes from having their holes on the topmost and bottommost positions respectively, as this would be an impossible pattern to pass through.
        uint8_t height = random(MAX_HOLE_HEIGHT+1); 
        if (pipes[lastPipe].holeHeight == MAX_HOLE_HEIGHT && height == 0) height++;
        pipes[i].holeHeight = height;

        lastPipe = i;
    }

    // Other:
    points = 0;

    timerBird[0] = Timer();
    if (numOfPlayers == 2) timerBird[1] = Timer();
    timerPipes = Timer();
}

void FlappyBird::playGame() {
    // Don't allow players to fly up by holding the joystick pressed instead of clicking it repeatedly.
    bool oldIsClicked[2] = {false, false};

    while (1) {
        bool isClicked[2] = {isJoystickPressed(0), isJoystickPressed(1)};

        // Move the bird to its new location on the screen: (when the joystick is clicked or when enough time has passed)
        for (uint8_t i = 0; i < numOfPlayers; i++) {
            if ((isClicked[i] != oldIsClicked[i] && isClicked[i]) || timerBird[i].elapsedPeriod(bird[i].getSpeed())) {
                // If the joystick was clicked, move the bird one pixel upwards:
                if (isClicked[i] != oldIsClicked[i] && isClicked[i]) {
                    moveBird(i, true);
                    timerBird[i].reset(); // It's necessary to reset the clock manually in this case.
                }
                // Otherwise, enough time has passed and the bird should move one pixel downwards:
                else 
                    moveBird(i, false);

                // Check for collision (and thus if the game is over):
                collision();
                if (gameover == true) return;
            }
        }

        // If enough time has passed, advance all pipes one column to the left.
        if (timerPipes.elapsedPeriod(PIPES_SPD)) {
            movePipes();

            // Check for collision (and thus if the game is over):
            collision();
            if (gameover == true) return;
        }

        // Forces players to let go of their joysticks and to press them again in order to make their birds fly up.
        oldIsClicked[0] = isClicked[0];
        if (numOfPlayers == 2) oldIsClicked[1] = isClicked[1];

        // Delay needed because of the used hardware (when the joystick is being released, there is a short interval where it's considered as being pressed again).  
        delay(50);
    }
}

bool FlappyBird::checkForVictory() {
    if (points == POINTS_FOR_VICT) { 
        playMelody(MLD_VCT_1_FREQS, MLD_VCT_1_DURS, MLD_VCT_1_BREAKS);
        gameover = true;
    }
}

void FlappyBird::displayResult() {
    uint8_t ones = points % 10;
    uint8_t tens = points / 10;

    uint16_t image[ROWS_CNT];
    // Create a complete image which will be displayed on the screen row by row:
    for (uint8_t i = 0; i < ROWS_CNT; i++) {
        image[i] = (pgm_read_byte(&DRW_DIGIT[ones][i]) << (ones == 1 ? 9 : 8));
        image[i] |= (pgm_read_byte(&DRW_DIGIT[tens][i]) << 12);
        
        if (points == POINTS_FOR_VICT) image[i] |= (pgm_read_byte(&DRW_CROWN[i]) << 1);
        else image[i] |= pgm_read_byte(&DRW_PIPES[i]);
    }
    
    // Show the created image on the screen:
    display->drawImage(image, false);
}


/// Additional methods for in-game logic:
void FlappyBird::moveBird(uint8_t birdId, bool upwards) {
    display->changePixel(bird[birdId].getColumn(), bird[birdId].getHeight(), LOW);
    bird[birdId].move(upwards);
    display->changePixel(bird[birdId].getColumn(), bird[birdId].getHeight(), HIGH);
}

void FlappyBird::movePipes() {
    for (uint8_t i = 0; i < PIPES_CNT; i++) {
        // Erase the screen column in which the pipe currently is:
        if (pipes[i].column >= COLS_CNT) continue; // Pipe hasn't reached the rightmost column of the screen yet (it's not even on the screen yet).
        else display->drawCol(pipes[i].column, 0);
        
        // If a bird is currently in the same column as this pipe:
        for (uint8_t j = 0; j < numOfPlayers; j++) {
            if (bird[j].getColumn() == pipes[i].column) {
                // Redraw the bird because it got erased along with the pipe.
                display->changePixel(bird[j].getColumn(), bird[j].getHeight(), HIGH);

                playSound(NOTE_G5, 60);
                if (j == 0) points++;    // Points are increased only when the leftmost bird has passed through the pipe in case of a multiplayer game.
                checkForVictory();
            }
        }
    }

    // If a pipe has reached the leftmost column on the screen, it is repositioned back behind the rightmost column of the screen and used as a new incoming pipe.
    // Special case: if the victory is near, we don't need any more incoming pipes. 
    //               In this case, the pipe will be moved all the way back and it will never reach the screen again.  
    for (uint8_t i = 0; i < PIPES_CNT; i++) {
        if (pipes[i].column == 0) { 
            // Incoming pipes = pipes currently on screen minus pipes left of the bird (in case of a multiplayer game, left of the leftmost bird).
            uint8_t leftBirdCol = numOfPlayers == 1 ? BIRD_COL : BIRDS_COL[0];
            uint8_t incomingPipes = PIPES_CNT - (1 + leftBirdCol/(PIPES_SPACE+1));
            if (points + incomingPipes == POINTS_FOR_VICT) pipes[i].column = -1;
            else pipes[i].column = pipes[lastPipe].column + PIPES_SPACE + 1;

            // Prevent neighboring pipes from having their holes on the topmost and bottommost positions respectively, as this would be an impossible pattern to pass through.
            uint8_t height = random(MAX_HOLE_HEIGHT+1); 
            if (pipes[lastPipe].holeHeight == MAX_HOLE_HEIGHT && height == 0) height++;
            pipes[i].holeHeight = height;

            lastPipe = (lastPipe + 1) % PIPES_CNT;

            break;
        }
    }

    // Advance the pipes:
    for (uint8_t i = 0; i < PIPES_CNT; i++) {
        pipes[i].column = pipes[i].column - 1;

        // Construct pipe's binary representation:
        if (pipes[i].column >= COLS_CNT) continue;     // Pipe still hasn't reached the screen.
        uint8_t hole = (1 << HOLE_SIZE) - 1;           // Binary representation of a hole on the bottommost position (ones represent the hole, zeros represent the pipe)
        uint8_t value = ~(hole << (ROWS_CNT - HOLE_SIZE - pipes[i].holeHeight));  // Position the hole on the needed height and invert the binary value 
                                                                                  // so that now the zeros represent the hole and ones represent the pipe.
        // If there is a bird in the column the pipe will advance to, keep it on screen as well.
        for (uint8_t j = 0; j < numOfPlayers; j++) {
            if (bird[j].getColumn() == pipes[i].column)
                value |= (0x80 >> bird[j].getHeight());
        }

        // Draw the pipe on it's new column.
        display->drawCol(pipes[i].column, value);
    }
}

// Checks if a bird is in the same column as one of the pipes, and then compares the height of the bird with the height of the pipe's hole.
// Also checks if a bird fell through the bottom of the screen since this is also considered as a loss. 
void FlappyBird::collision() {
    bool didCollide = false;

    for (uint8_t i = 0; i < numOfPlayers; i++) {
        for (uint8_t j = 0; j < PIPES_CNT; j++) {
            if (bird[i].getColumn() == pipes[j].column  &&
               (bird[i].getHeight() < pipes[j].holeHeight || 
                bird[i].getHeight() >= pipes[j].holeHeight + HOLE_SIZE)) {

                didCollide = true;
                break;
            }
        }
    }

    // If a bird collided with the pipes or if it fell through the bottom of the screen:
    if (didCollide || bird[0].getHeight() == (uint8_t)-1 || 
        (numOfPlayers == 2 && bird[1].getHeight() == (uint8_t)-1)) {
            
        playMelody(MLD_DFT_FREQS, MLD_DFT_DURS, MLD_DFT_BREAKS);
        gameover = true;
        delay(1000);
    }
}