# Computer games design based on the application of a microcontroller
This software was developed as a result of my Bachelor Thesis titled "Computer games design based on the application of a microcontroller" under the mentorship of [Assoc. Prof. Nadica Miljković](https://www.etf.bg.ac.rs/en/faculty/staff/nadica-miljkovic-4323) from the [University of Belgrade - School of Electrical Engineering](https://www.etf.bg.ac.rs/en) defended on September 24, 2024.

A video that demonstrates all the features of the finished project is available on [YouTube](https://www.youtube.com/) (Google LLC, San Bruno, California, USA) and it can be accessed via the following [link](https://youtu.be/TDOLidR57ME).

### Table of Contents
1. [Introduction](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md#1-introduction)
2. [Software and Hardware Requirements](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md#2-software-and-hardware-requirements)
3. [User Interface Overview](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md#3-user-interface-overview)
4. [Game Controls](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md#4-game-controls)
5. [Citing Instructions](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md#5-citing-instructions)

***
### 1. Introduction
The goal of this project was to build a fully functional game console using some of the simplest hardware components available and to program a set of games that could be played on it. An [Arduino](https://www.arduino.cc/) microcontroller board was used as the core of the console to execute source code and to communicate with all of the used components. The console supports single-player and two-player versions of the following games: 
+ [Snake](https://en.wikipedia.org/wiki/Snake_(1998_video_game)) (Taneli Armanto, Nokia, Espoo, Finland)
+ [Pong](https://en.wikipedia.org/wiki/Pong) (Allan Alcorn, Atari, Sunnyvale, California, USA)
+ [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird) (Dong Nguyen, .Gears, Hanoi, Vietnam)

The games themselves are not original, but their implementations were developed independently in [C++](https://isocpp.org/) programming language without seeking other people's ideas or solutions. In order to make the code more readable and to simplify the management of individual components, some additional libraries were also manually written. However, the source code does rely on the following list of public libraries and header files as well, in their original forms:
+ [LedControl library](http://wayoda.github.io/LedControl/index.html) - Developed by [Eberhard Fahle](https://github.com/wayoda), accessed on November 8, 2024
+ [pitches.h file](https://github.com/arduino/arduino-examples/blob/main/examples/02.Digital/toneMelody/pitches.h) - Part of an Arduino built-in example, accessed on November 8, 2024

The code also uses functionalities provided by libraries that are an integral part of the Arduino UNO R3 microcontroller board and, as such, these libraries are not a part of this repository (e.g. [Arduino.h](https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h), [avr/progmem.h](https://github.com/avrdudes/avr-libc/blob/main/tests/simulate/progmem.h) and [stdint.h](https://github.com/codebendercc/arduino-core-files/blob/master/v102/hardware/tools/avr/lib/avr/include/stdint.h)).

**DISCLAIMER:** Although the project as a whole is under the [GNU GPL (General Public License) Version 3+ license](https://github.com/aleva147/Arduino-Game-Console/blob/main/LICENSE), the [LedControl](http://wayoda.github.io/LedControl/index.html) library has its own [license](https://github.com/aleva147/Arduino-Game-Console/blob/main/libraries/Display/LICENSE) located in the [Libraries/Display directory](https://github.com/aleva147/Arduino-Game-Console/tree/main/libraries/Display). It is important to read this license and to follow its obligations should you choose to work on this project.

This repository contains:
+ [Console](https://github.com/aleva147/Arduino-Game-Console/tree/main/Console) directory in which the main Arduino sketch ([Console.ino](https://github.com/aleva147/Arduino-Game-Console/blob/main/Console/Console.ino)) is located
+ [libraries](https://github.com/aleva147/Arduino-Game-Console/tree/main/libraries) directory which contains all of the libraries used by the game console that are not an integral part of the Arduino UNO microcontroller board
+ [GNU GPL (General Public License) Version 3+ license](https://github.com/aleva147/Arduino-Game-Console/blob/main/LICENSE)
+ [README.md](https://github.com/aleva147/Arduino-Game-Console/blob/main/README.md) file
+ [CITATION.cff](https://github.com/aleva147/Arduino-Game-Console/blob/main/CITATION.cff) file used to generate the "Cite this repository" link on the GitHub page

The following chapters will explain:
+ How to assemble the described game console and to run the written software on it
+ What the user interface looks like
+ How to play each version of every available game

***
### 2. Software and Hardware Requirements

Software:
+ Linux OS, Windows OS, or macOS
+ Arduino IDE

Hardware:
+ Arduino UNO R3
+ USB 2.0 cable type A/B
+ Breadboard
+ Analog joystick (x2)
+ 8x8 LED matrix display with the MAX72XX driver [1] (x2)
+ Passive buzzer
+ Jumper wire male to male (x9)
+ Jumper wire male to female (x15)
+ Resistor (not necessary)

The image below shows how the hardware should be assembled. It was created using [Wokwi](https://wokwi.com/) [2]. Since the identifiers of the used pins are not very clear on the image, pin identifiers can also be found inside the [Constants.h file](https://github.com/aleva147/Arduino-Game-Console/blob/main/libraries/Constants/Constants.h) which is located in the [libraries/Constants directory](https://github.com/aleva147/Arduino-Game-Console/tree/main/libraries/Constants).

![Assembled hardware](https://github.com/user-attachments/assets/c13ae912-dec7-459c-b54e-ff488e90118c)

In order to run the available source code on your hardware, follow these steps:
+ Download the code as a ZIP archive and extract its contents.
+ Move the [Console.ino](https://github.com/aleva147/Arduino-Game-Console/blob/main/Console/Console.ino) file to the directory where your Arduino IDE stores its sketches (this location can be found by opening Arduino IDE and clicking on File/Preferences).
+ Copy all of the downloaded [library folders](https://github.com/aleva147/Arduino-Game-Console/tree/main/libraries) to the libraries subfolder inside of the directory where Arduino IDE stores its sketches.   
+ Connect the Arduino UNO microcontroller board with your computer, open the copied Console.ino sketch in Arduino IDE and upload the sketch to the board.

References:<br>
[1] MAX72XX drivers are manufactured by Maxim Integrated (San Jose, California, USA).<br>
[2] Wokwi is a web simulator for embedded and IoT systems that assists in learning and planning embedded device interactions and programming. It is developed and operated by CodeMagic Ltd.

***
### 3. User Interface Overview
When using the console, the user will encounter three different interfaces:
+ Main menu
+ Player selection menu
+ Games themselves
  
The following image represents the main menu:

![Main menu](https://github.com/user-attachments/assets/58b391b9-921b-4b7f-bc35-4a12678ba829)

On the left half of the screen, there is a drawing of an arrow facing up and an arrow facing down. This is an indication to the user that it is possible to scroll through the list of available games by aiming either of the two joysticks up or down. A short looping animation of the currently selected game is displayed on the right half of the screen. In order to confirm the currently selected game and to advance to the player selection menu, move one of the joysticks to the right. 

The image below represents the player selection menu:

![Player selection](https://github.com/user-attachments/assets/2531f64a-f576-457c-bd56-6bae705f67e3)

Every game can be played by either one or two players. Change the number of players by moving one of the joysticks up or down. To confirm the selected number of players and to start the game, aim either of the two joysticks to the right.

The next image shows what the single-player version of each game looks like:

![Games overview](https://github.com/user-attachments/assets/a0353b9e-df0d-4ac9-ad15-07400db66930)

Before the selected game begins, a short countdown is always shown to let the players get ready. After the end of the game, the achieved score is shown on the screen and users can either return to the main menu by aiming one of the joysticks to the left, or play the game again by aiming either joystick to the right. The specific controls for both versions of every available game are explained in the next chapter of this document.

***
### 4. Game Controls

#### Snake
The snake will always spawn near the bottom-left corner of the screen and its initial direction will be to the right. Use the left joystick to change the direction in which the snake is heading. If the joystick is aimed diagonally, the game won't know whether to change the snake's horizontal or vertical direction, and the snake will just continue heading in its current direction. So, make sure to aim the joystick as precisely as possible to avoid undetected commands. If the snake runs into one of the walls or into its own body, the player will lose and the game will end. The player will win if he/she collects 127 apples.

In case of a two-player game, the second snake will always spawn near the bottom left corner of the right half of the screen and its initial direction will also be to the right. Use the right joystick to control the second snake's movement. The snakes must avoid each other while trying to collect the apples together. The game will end in victory if the total length of the two snakes is the greatest possible (128).  

#### Pong
When playing a single-player game, use the left joystick to move the racket along the left border of the screen by aiming the joystick up or down. It's important to keep the joystick aimed in the desired direction until the racket moves to a new position. Otherwise, if you only quickly push the joystick up or down and then let go, the movement won't be registered and the racket will stay in place. Unlike the other games, Pong has multiple rounds. This means that the game will end once someone reaches 3 points and only then will it be possible to return to the main menu or to start a new game.

The same rules apply for the two-player version of the game as well. The racket on the right half of the screen is controlled by the second player using the right joystick.

#### Flappy Bird
Every time the left joystick is clicked, the bird will fly up by one pixel and its falling speed will reset to the initial value. The longer the joystick isn't pressed, the faster the bird falls. If the bird hits any of the incoming pipes or if the bird falls beneath the bottom border of the screen, the player will lose. To achieve victory, the bird needs to successfully pass through 50 obstacles. The game is intentionally hard, but there are no impossible pairs of incoming obstacles.

In the two-player version, each player has his/hers own bird and the birds need to pass through the incoming pipes together. To control the second bird, use the right joystick. The game will be harder for the second player since the second bird is closer to the right edge of the screen and there is less time to react. If either of the two birds collides with an obstacle or falls through the bottom border of the screen, the game ends for both players.

***
### 5. Citing Instructions
If you find this software useful, please cite my bachelor thesis and this repository as:
+ Vagner, A. (2024). Computer games design based on the application of a microcontroller. *Bachelor Thesis, University of Belgrade - School of Electrical Engineering*, mentor: Dr. Nadica Miljković.
+ Vagner, A. (2024). Computer games design based on the application of a microcontroller (Version 1.0) [Computer software]. https://github.com/aleva147/Arduino-Game-Console, Accessed on November 8, 2024.


CONTACT: Aleksandar Vagner ([LinkedIn](http://linkedin.com/in/aleksandarvagner))
