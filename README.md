Assignment 2 – FINITE STATE MACHINE
 
ABSTRACT


The single player version of famous pong game was implemented using Teensy 3.2 development board, Push buttons, Potentiometer, and SSD1306 OLED display.
The game is implemented as state machine with 
1.	Start Screen
2.	Game Screen  
3. Pause Screen
4.	End Screen

The Start, Pause and Resets are controlled by push buttons whereas the potentiometer controls the paddle for the player.
The debouncing of Start/Pause button and Reset Button is successfully implemented within the program.


OBJECTIVE

•	The main objective of this assignment is to develop a game, which need to be implemented as state machine.

•	The sub objectives are as follows:

     The Game must include:-
     
I.	Start Screen

II.	Game Screen and

III.	End Screen

•	Included Button debouncing 


DESIGN 


Working


The design is a simple pong game which is modified for the player to play the game between Player and Teensy. Teensy is assigned to the left of the screen and the player is assigned to the right of the screen, where the player‘s paddle is manually controlled using the potentiometer. 

The game is designed in such a way that the if any of the player miss the ball and it hits on the wall the opposite player will gain a point. The score required to win the match is 4.The scores are updated on the screen.


Pin Allocation


The pin allocated to control the game are as follows:

Start/ Pause – Digital Pin 11 (Left push button)

Reset - Digital pin 12 (Right Push Button)

Player’s Paddle control – Analog Pin 06 (Potentiometer)

Game Control


To start the game Push the start / Pause button. If the Game is in a running state and need a pause start the Start or Pause button again to pause i.e., change of state. To reset the game press reset button.

 For the player to control the paddle to avoid missing the ball , turn the potentiometer in such a way that the paddle moves in up/down direction to hit the ball back to the opposite player (teensy)

