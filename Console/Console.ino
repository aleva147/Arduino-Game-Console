#include <Joystick.h>
#include <Display.h>
#include <Buzzer.h>
#include <Timer.h>
#include <Snake.h>
#include <Pong.h>
#include <FlappyBird.h>


// Common objects:
Display display = Display();

// Main menu constants:
const uint8_t ANIMATION_SPD = 250;
// Main menu variables:
uint8_t chosenGame          = 0;
uint8_t chosenNumOfPlayers  = 1;
uint8_t currentImg          = 0;  // Used for animating the icon of the currently selected game in the main menu.



void setup() {
  // Screen initialization:
  display.initialize(4);  // Argument represents the light intensity of the screen (max possible value: 16). 
  
  // Joystick initialization:
  initializeJoysticks();

  // Buzzer initialization:
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUZZER, HIGH);

  // Debug:
//  Serial.begin(9600);
  
  // Startup animation and melody:
  turnOnConsole();
}


void loop() {	
  // Show the main menu:
  mainMenu();

  // Show the player selection menu:
  playerSelection();

  // Initialize the pseudorandom number generator:
  randomSeed(millis()); // The time instant when a game is selected is used as a source of randomness.

  // Run the selected game:
  Game* game;
  switch (chosenGame) {
    case 0: game = new Pong(&display); break;
    case 1: game = new Snake(&display); break;
    case 2: game = new FlappyBird(&display); break;
  }
  game->startGame(chosenNumOfPlayers);

  // Leave the game:
  delete game;
  leaveGame();  // Wipes the screen from right to left and plays the melody.             
}



// MAIN MENU FUNCTIONS:
void mainMenu() {
  Timer timer = Timer();  // Timer used to animate the icon of the currently selected game in the main menu.
  
  drawMainMenu();

  while(1) {
    // Process user input:
    if (isSomeJoystickAimed(DOWN)) {
      changeGame(DOWN);
    }
    else if (isSomeJoystickAimed(UP)) {
      changeGame(UP);
    }
    else if (isSomeJoystickAimed(RIGHT)) {
      playMelody(MLD_ENT_1_FREQS, MLD_ENT_1_DURS, MLD_ENT_1_BREAKS);
      display.horizontalWipe(RIGHT);
      return;
    }

    // Animate the game icon on the right half of the screen:
    if (timer.elapsedPeriod(ANIMATION_SPD)) {
      currentImg = (currentImg + 1) % ANIM_GAME_LEN;
      display.drawImage(1, ANIM_GAME[chosenGame][currentImg], true);
    }
  }
}

void drawMainMenu() {
  // Construct the complete image which will be displayed on the screen, row by row:
  uint16_t image[ROWS_CNT];
  for (int i = 0; i < ROWS_CNT; i++) {
    image[i] = pgm_read_byte(&DRW_MENU_ARROW_UP[i]) << 8;
    image[i] |= pgm_read_byte(&DRW_MENU_ARROW_DOWN[i]) << 8;
    image[i] |= pgm_read_byte(&ANIM_GAME[chosenGame][currentImg][i]);
  }

  // Show the constructed image on the screen:
  display.drawImage(image, false);
}

void changeGame(char arrow) {
  // While the right half of the screen is being wiped, show only the selected arrow on the left half of the screen: 
  if (arrow == DOWN) {
    playSound(NOTE_C5, 125);
    display.drawImage(0, DRW_MENU_ARROW_DOWN, true);
  }
  else {
    playSound(NOTE_D5, 125);
    display.drawImage(0, DRW_MENU_ARROW_UP, true);
  }

  // Wipe the right half of the screen in the chosen direction:
  display.verticalWipe(1, (arrow == DOWN ? DOWN : UP));

  // Update the currently selected game:
  if (arrow == DOWN && chosenGame-- == 0) chosenGame = NUM_OF_GAMES - 1;
  if (arrow == UP && ++chosenGame == NUM_OF_GAMES) chosenGame = 0;

  // Show both arrows on the left half of the screen again:
  uint8_t image[ROWS_CNT];
  for (uint8_t i = 0; i < ROWS_CNT; i++) {
    image[i] = pgm_read_byte(&DRW_MENU_ARROW_DOWN[i]) | pgm_read_byte(&DRW_MENU_ARROW_UP[i]);
  }
  display.drawImage(0, image, false);

  // Reset the animation of the game icon to its initial frame:
  currentImg = 0;
}


// FUNCTIONS FOR PLAYER SELECTION:
void playerSelection() {
  drawPlayerSelection();

  // Prevents players from accidentally confirming the number of players immediately after selecting a game.
  delay(1000);  

  // Process user input:
  while (1) {
    if (isSomeJoystickAimed(DOWN) && chosenNumOfPlayers > 1) {
      playSound(NOTE_C5, 125);
      chosenNumOfPlayers--;
      drawPlayerSelection();
    }
    else if (isSomeJoystickAimed(UP) && chosenNumOfPlayers < JOYSTICKS_CNT) {
      playSound(NOTE_D5, 125);
      chosenNumOfPlayers++;
      drawPlayerSelection();
    }
    else if (isSomeJoystickAimed(RIGHT)) {
      playMelody(MLD_ENT_2_FREQS, MLD_ENT_2_DURS, MLD_ENT_2_BREAKS);
      display.horizontalWipe(RIGHT);
      return;
    }
  }
}

void drawPlayerSelection() {
  int image[ROWS_CNT];
  // Bold digit on the left half of the screen, human figure on the right half of the screen.
  for (int i = 0; i < ROWS_CNT; i++) {
    image[i] = pgm_read_byte(&DRW_BOLD_DIGIT[chosenNumOfPlayers-1][i]) << 8;
    image[i] |= pgm_read_byte(&DRW_HUMAN[i]);
  } 
  display.drawImage(image, false);
}


// FUNCTIONS FOR TURNING THE DEVICE ON AND LEAVING:
void turnOnConsole() {
	for (uint8_t frame = 0, note = 0; frame < ANIM_TURN_ON_LEN; frame++, note++) {
    // Show the current image:
    display.drawImage(ANIM_TURN_ON[frame], true);

		// Play the current sound form the turn on melody:
		playSound(pgm_read_word(&MLD_TURN_ON_FREQS[note+1]), pgm_read_byte(&MLD_TURN_ON_DURS[note]));
		delay(pgm_read_word(&MLD_TURN_ON_BREAKS[note]));
	}

	display.clear();
	delay(200);
}

void leaveGame() {
  playMelody(MLD_EXT_FREQS, MLD_EXT_DURS, MLD_EXT_BREAKS);
  display.horizontalWipe(LEFT);
}
