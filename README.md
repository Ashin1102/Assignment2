                                            
  ![IMG_2503](https://user-images.githubusercontent.com/53546301/69683549-0b9ecd80-111a-11ea-96f9-b2a1eefb8fdd.jpg)
                                            
                                            
                                            
                                            Assignment 2 – FINITE STATE MACHINE
 
        i. ABSTRACT


A single player version of pong game was implemented using Teensy 3.2 development board, Push buttons, Potentiometer, and SSD1306 OLED display.
The project is implemented as state machine with multiple state, as follows:
1.	Start Screen
2.	Game Screen  
3. Pause Screen
4.	End Screen

The Start, Pause and Resets are controlled by push buttons whereas the potentiometer controls the paddle for the player.
The debouncing of Push Buttons are also implemented within the program.


        ii. OBJECTIVE

•	The main objective of this assignment is to develop a game, which need to be implemented as a state machine.

•	The sub objectives are as follows:

    The state machine must include Four different state
     
I.	Start Screen

II.	Game Screen and

III.	End Screen

•	Included Button debouncing 




          iii.METHODOLOGY
          
          

  ![circuit](https://user-images.githubusercontent.com/53546301/69624368-7106a600-10a9-11ea-9371-55554e8b4444.jpg)
 
•	The teensy 3.2 digital in have an output of 3.3v and up to 10Ma.

•	The OLED display’s SDA, SCK, VCC and Ground pins are connected to the micro controller pin 18, 19, VCC and ground. The display uses an   i2c communication protocol with a communication address of Ox3Ce.

•	The Potentiometer is connected across the analog pin A6 which is designed to control the player paddle

•	The  Start/ Pause and reset push buttons activate the software interrupt by pulling the microcontroller pins 11 and 12 to ground these   are internally pulled up to avoid floating

•	The Start /Pause button carries the function of Start or Pause depending on the current state of the game.

•	The reset button is caries the function of resetting the game

   ![pin](https://user-images.githubusercontent.com/53546301/69624375-72d06980-10a9-11ea-88b0-a2b98a82e587.jpg)


            iv.COMPONENTS SELECTION
            

  ![IMG_2495](https://user-images.githubusercontent.com/53546301/69625575-bdeb7c00-10ab-11ea-97c3-cc0afb2683f8.JPG)
   

•	Here I have used two push buttons for start/Pause and reset function, which are used for hardware interrupts. 

•	To control the player’s paddle I have used 10 Kohm potentiometer by mapping the analog input with respect to screen height.

•	A 128 x 64 monochrome display running on SSD1306 driver communicated via i2c interface is used for displaying the game states.


             v.DESIGN 


1.Working


The design is a simple pong game which is modified for the player to play the game between Player and Teensy. Teensy is assigned to the left of the screen and the player is assigned to the right of the screen, where the player‘s paddle is manually controlled using the potentiometer. 

The game is designed in such a way that the if any of the player miss the ball and it hits on the wall the opposite player will gain a point. The score required to win the match is 4.The scores are updated on the screen.


2.Pin Allocation


The pin allocated to control the game are as follows:

Start/ Pause – Digital Pin 11 (Left push button)

Reset - Digital pin 12 (Right Push Button)

Player’s Paddle control – Analog Pin 06 (Potentiometer)

3.Game Control


To start the game Push the start / Pause button. If the Game is in a running state and need a pause start the Start or Pause button again to pause i.e., change of state. To reset the game press reset button.

 For the player to control the paddle to avoid missing the ball , turn the potentiometer in such a way that the paddle moves in up/down direction to hit the ball back to the opposite player (teensy)
 

           vi. RESULT

1.Testing and Verification


  ![Blank Diagram](https://user-images.githubusercontent.com/53546301/69626899-72869d00-10ae-11ea-8b7a-5923be0353cd.jpeg)

The stages of the FSM are tested .The tested four stages are as follows:

Sate1 – Start_Game

State2 – Play_Game

State 3 – Pause_Game

State 4 – End_Game

The testing results of the above stages are follows



Test 1


Start_ Game  Screen




It is the initial state of the game. This state gives the instruction on how to access the game screen, what is the target of each player to win the game. The below image is the display of the start screen.


![IMG_2464](https://user-images.githubusercontent.com/53546301/69678413-60d2e300-110a-11ea-8c7d-fd4e29afd349.JPG)


Playing Screen


The below image shows the “playing screen” of the game on the screen. This screen popups when the Start button is pressed as per the instruction given in the start screen. I this screen the actual match between the “Teensy player” and the “Player X” take place. Whenever any of the players gain a point, the score card will get automatically updated. 


![IMG_2465](https://user-images.githubusercontent.com/53546301/69678469-7ea04800-110a-11ea-8a19-4cebfd1eafc4.JPG)

Test 3

Pause _Game Screen


The below image shows the “pause” stage of the game on the screen. In this case if the match between the “Teensy player “and the “Player X” is going on as the game is in playing state and if the manual player want a sudden pause from the game, by Pressing the start  button again ,the game will get pause unless the start button is again toggled .

![IMG_2466](https://user-images.githubusercontent.com/53546301/69678489-92e44500-110a-11ea-8e88-e9ab6c9f002e.JPG)

Test 4

End_Game  Screen



The below image shows the End screen of the game on the screen as any of the player achieved the target score. If the Teensy player wins the end screen displays “TEENSY WON” or in other case it displays “PLAYER X WON”. Moreover, it also provides the instruction on how to restart the game.


![IMG_2467](https://user-images.githubusercontent.com/53546301/69678544-c1fab680-110a-11ea-8a05-1dee4fbc1ae7.JPG)



2. Signal Integrity


   i.	Here the value of Pull-Up resistor used in SSD1306 display device is 4.7KΩ 

   ii.	The Wave form  for i2c  Clock and Data signal is captured

CLOCK LINE – SCK

The connection is made between SCK and GND pin of the SSD1306 Display to Channel 1 of Digital Oscilloscope. The resulting waveform is as follows

 ![0](https://user-images.githubusercontent.com/53546301/69634211-a1a10c80-10b6-11ea-87ba-2bd20a77cc50.jpg)



DATA LINE - SDA

The connection is made between SDA and GND pin of the SSD1306 Display to Channel 1 of Digital Oscilloscope. The resulting waveform is as follows


![sck](https://user-images.githubusercontent.com/53546301/69634284-c85f4300-10b6-11ea-9e6f-20ca1b79a420.jpg)





BY change in the value of PULL UP resistance there will be an increase or decrease in flow of current which affects  the charging  interval of bus capacitor. This change in  would severely affect the communication between Teensy and the display. Higher the resistance value increase the capacitance charging time or vice versa. Having too high bus capacitance will not let the threshold on the receiver to be reached. By using a proper value of Resistance could partially avoid this adverse effect,that would limit the negetive impact on signal integrity.


3.SOURCE CODE

A well commented source code for my assignment is visinle at https://github.com/Ashin1102/Assignment2/blob/master/src/main.cpp file

4.VIDEO LINK

  https://youtu.be/lh-0LcUJhdE

           vii.LIMITATIONS
           
  Eventhough the game is working fine, the ball movement is in a constant speed.The future improvemments can be made by improving the ball speed to upgrade with different levels for the pong game.
  
            iX.APPENDIX
        
  1. https://www.pjrc.com/teensy/card7a_rev1.pdf
  2. https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf


          X REFERENCES
          
(n.d.). Retrieved from https://components101.com/oled-display-ssd1306
(n.d.). Retrieved from https://www.youtube.com/watch?v=Sb83upcxNVk&t=87s
(n.d.). Retrieved from https://github.com/shveytank/Arduino_Pong_Game/blob/master/Arduino_Pong_Game.ino
(n.d.). Retrieved from https://learn.adafruit.com/monochrome-oled-breakouts/wiring-128x64-oleds
(n.d.). Retrieved from https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples

