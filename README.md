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


METHODOLOGY
![circuit](https://user-images.githubusercontent.com/53546301/69624368-7106a600-10a9-11ea-9371-55554e8b4444.jpg)
 
•	The teensy 3.2 digital in have an output of 3.3v and up to 10Ma.

•	The OLED display’s SDA, SCK, VCC and Ground pins are connected to the micro controller pin 18, 19, VCC and ground. The display uses an i2c communication protocol with a communication address of Ox3Ce.

•	The Potentiometer is connected across the analog pin A6 which is designed to control the player paddle

•	The  Start/ Pause and reset push buttons activate the software interrupt by pulling the microcontroller pins 11 and 12 to ground these are internally pulled up to avoid floating

•	The Start /Pause button carries the function of Start or Pause depending on the current state of the game.

•	The reset button is caries the function of resetting the game

![pin](https://user-images.githubusercontent.com/53546301/69624375-72d06980-10a9-11ea-88b0-a2b98a82e587.jpg)


Components Selection

![IMG_2495](https://user-images.githubusercontent.com/53546301/69625575-bdeb7c00-10ab-11ea-97c3-cc0afb2683f8.JPG)

•	Here I have used two push buttons for start/Pause and reset function, which are used for hardware interrupts. 

•	To control the player’s paddle I have used potentiometer by mapping the analog input with respect to screen height.

•	A 128 x 64 monochrome display running on SSD1306 driver communicated via i2c interface is used for displaying the game states.


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

Testing and Verification

The stages of the FSM are tested .The tested four stages are as follows:

Sate1 – Start Game

State2 – Playing stage

State 3 – Pause Game

State 4 – Game Ends

The testing results of the above stages are follows

Test 1

Start_ Game  Screen

![IMG_2464](https://user-images.githubusercontent.com/53546301/69625726-1d498c00-10ac-11ea-9649-3256c691cc86.JPG)



It is the initial state of the game. This state gives the instruction on how to access the game screen, what is the target of each player to win the game. The below image is the display of the start screen.




Test 2

Playing Screen

![IMG_2465](https://user-images.githubusercontent.com/53546301/69625977-921cc600-10ac-11ea-9505-369561ea2bf3.JPG)





The below image shows the “playing screen” of the game on the screen. This screen popups when the Start button is pressed as per the instruction given in the start screen. I this screen the actual match between the “Teensy player” and the “Player X” take place. Whenever any of the players gain a point, the score card will get automatically updated. 



Test 3

Pause _Game Screen

![IMG_2466](https://user-images.githubusercontent.com/53546301/69626562-c1800280-10ad-11ea-91a0-3dda40453d92.JPG)



The below image shows the “pause” stage of the game on the screen. In this case if the match between the “Teensy player “and the “Player X” is going on as the game is in playing state and if the manual player want a sudden pause from the game, by Pressing the start  button again ,the game will get pause unless the start button is again toggled .

Test 4

End_Game  Screen

![IMG_2467](https://user-images.githubusercontent.com/53546301/69626706-06a43480-10ae-11ea-9345-a2fac51b9f25.JPG)

The below image shows the End screen of the game on the screen as any of the player achieved the target score. If the Teensy player wins the end screen displays “TEENSY WON” or in other case it displays “PLAYER X WON”. Moreover, it also provides the instruction on how to restart the game.


