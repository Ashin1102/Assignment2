//Libraries
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//Interupt and control Allocation
#define Start_button 12 //Pin 12
#define Reset_button 11 //Pin 11
#define Paddle_control A6 //potentiometer for paddle control


uint32_t debounceDelay = 150; //Bounce ignoring time          
volatile uint32_t lastDebounceTime = 0; // flag to store last bounce update
volatile bool debounceDelayflag = LOW; // debounce delay updation


const unsigned long PADDLE_RATE = 1; // time for updating paddle psition
const unsigned long BALL_RATE = 36; // time for updating ball psition
const uint8_t PADDLE_HEIGHT = 24; 
// OLED pixels
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
// SSD1306 with i2C -data and clock pins
#define OLED_RESET 4 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ball position and direction
unsigned long ball_update;
uint8_t ball_x = 64, ball_y = 32; //initial position
uint8_t ball_x_dir = 1, ball_y_dir = 1; //initial direction

//Teensy paddle
unsigned long paddle_update;
const uint8_t TSY_X = 12; // starting position
uint8_t tsy_y = 16;
//Player_X Paddle
const uint8_t PLAYER_X = 115; 
uint8_t player_y = 15;

uint8_t Teensy_points = 0;
uint8_t Player_points = 0;
//Flags for updation on Start/Pause and Reset Button
bool StartPause_Flag = LOW; // High if paused
bool Reset_Flag = LOW; // High if reset toggled
bool StartPause_Toggle = LOW; // Button Update flag

//Four states of State machine
enum States 
{
    Start_Game,
    Play_Game,
    Pause_Game,
    End_Game
};
States current_state = Start_Game; // Current state

void display_start_screen()
{
    uint8_t ball_x = 64, ball_y = 32; //Ball position Reset
    uint8_t ball_x_dir = 1, ball_y_dir = 1; //Ball direction reset
    
// Start Screen Display 

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println(F("  Teensy VS PlayerX"));


    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30, 25);
    display.println(F("GAME TARGET-4"));
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 40);
    display.println(F("Press "));
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(50, 40);
    display.println(F("START "));

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 55);
    display.println(F("to Continue..... "));
    display.display();

 
    StartPause_Flag = 0;
    Teensy_points = 0;
    Player_points = 0;
}

bool setup_game_screen(bool finished_game_screen_setup)
{
    finished_game_screen_setup = false;
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, WHITE);

// Score board in Play state

 
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(50, 15);
    display.print("T-");
    display.print(Teensy_points);
    display.setCursor(71, 15);
    display.print("|");
    display.setCursor(80, 15);
    display.print("P-");
    display.print(Player_points);
    display.display();
    finished_game_screen_setup = true;
    return finished_game_screen_setup;
}
// Score bord updation

void update_score_board()
{
    
    display.clearDisplay();
    display.drawRect(0, 0, 128, 64, WHITE);
    display.setTextSize(1); 
    display.setTextColor(WHITE);
    display.setCursor(50, 15);
    display.print("T-");
    display.print(Teensy_points);
    display.setCursor(71, 15);
    display.print("|");                                                                                                           
    display.setCursor(80, 15);
    d  display.print(Player_points);
    // Pause screen
    if(current_state == Pause_Game){
        display.setTextSize(2); 
        display.setTextColor(WHITE);
        display.setCursor(30, 30);
        display.println("PAUSED");
    }
    display.display();
}

void run_game()
{
    unsigned long time = millis();
    if (time > ball_update)
    {
        uint8_t Wall_x = ball_x + ball_x_dir; 
        uint8_t Wall_y = ball_y + ball_y_dir;

       // TO check if ball hit the vertical walls
        if (Wall_x == 0 || Wall_x == 127)
        {
            // Score updation depending on the side of the wall
            if (Wall_x == 0)
            {
                Player_points = Player_points + 1;
            }

            if (Wall_x == 127)
            {
                Teensy_points = Teensy_points + 1;
            }

            ball_x_dir = -ball_x_dir;
            Wall_x += ball_x_dir + ball_x_dir;

            update_score_board();
        }

// to check if ball it on horizondal walls
       
        if (Wall_y == 0 || Wall_y == 63)
        {
            ball_y_dir = - ball_y_dir; // setting next ball pixel
            Wall_y +=  ball_y_dir +  ball_y_dir;
        }

// checking the ball hit on teensy paddle  
        if (Wall_x == TSY_X && Wall_y >= tsy_y && Wall_y <= tsy_y + PADDLE_HEIGHT)
        {
             ball_x_dir = -ball_x_dir;
            Wall_x += ball_x_dir + ball_x_dir;
        }

        // checking the ball hit on player paddle  
        if (Wall_x == PLAYER_X && Wall_y >= player_y && Wall_y <= player_y + PADDLE_HEIGHT)
        {
            ball_x_dir = -ball_x_dir;
            Wall_x += ball_x_dir + ball_x_dir;
        }

        if ((ball_x > 48 and ball_x < 88) and (ball_y > 4 and ball_y < 12))
        {
           
        }
        else
        {
            display.drawPixel(ball_x, ball_y, BLACK); 
            display.drawPixel(Wall_x, Wall_y, WHITE);
        }

        ball_x = Wall_x;
        ball_y = Wall_y;

        ball_update += BALL_RATE;

        display.display();
    }

    if (time > paddle_update)
    {
        paddle_update += PADDLE_RATE;

        
        display.drawFastVLine(TSY_X, tsy_y, PADDLE_HEIGHT, BLACK);
        const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
        if (tsy_y + half_paddle > ball_y) //CPU paddle movement
        {
            tsy_y -= 1;
        }
        if (tsy_y + half_paddle < ball_y)
        {
            tsy_y += 1;
        }

        if (tsy_y < 1)
        {
            tsy_y = 1;
        }
        if (tsy_y + PADDLE_HEIGHT > 63)
        {
            tsy_y = 63 - PADDLE_HEIGHT;
        }
        display.drawFastVLine(TSY_X, tsy_y, PADDLE_HEIGHT, WHITE);

       //Player paddle
        display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);

        player_y = map(analogRead(Paddle_control), 0, 926, 0, (63 - PADDLE_HEIGHT)); 
        display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);       

        display.display();
    }
}
//End Screen Dispaly
void display_end_screen()
{
    display.clearDisplay(); 
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(32, 8);
    display.println("GAME OVER !" );
    
    if (Teensy_points == 4)
    {
    display.setCursor(25, 20);
    display.print("Teensy Score - ");
    display.print( Teensy_points);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 30);
    display.println("Teensy Won");
        
    }
    else if (Player_points == 4)
    {
    display.setCursor(25, 20);
    display.print("Player Score - ");
    display.print( Player_points);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 30);
    display.println(" Player Won"); 
       
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 53);
    display.println("Press Reset....." );
    display.display();
}
// Switch Debouncing
void switch_bounce_handler() 
{
    if (millis() - lastDebounceTime >= debounceDelay)
    {
        debounceDelayflag = true;
        
    }
    else
    {
        debounceDelayflag = false;
        
    }
}
// Start or Pause handling 
void ISR_start_pause() 
{
    if (debounceDelayflag == true) 
    {
        StartPause_Flag = not StartPause_Flag;
        StartPause_Toggle = true; 
        lastDebounceTime = millis(); 
    }
}

// Reset handling
void ISR_reset() 
{
    if (debounceDelayflag == true) // if flag triggers , following fuction executes
    {
        Reset_Flag = true; 
        lastDebounceTime = millis(); 
    }
}
// initialising   
void setup() 
{
    Serial.begin(9600);

    if (! display.begin(SSD1306_SWITCHCAPVCC, 0x3C))// OLED display with adress 0x3C
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; 
    }

    // Pins Initialisation
    pinMode(Paddle_control, INPUT);
    pinMode(Start_button, INPUT_PULLUP);
    pinMode(Reset_button, INPUT_PULLUP);

//Interupt function when pins goes low
    attachInterrupt(digitalPinToInterrupt(Start_button), ISR_start_pause, FALLING);

    attachInterrupt(digitalPinToInterrupt(Reset_button), ISR_reset, FALLING);

    display.clearDisplay();

    ball_update = millis();
    paddle_update = ball_update;
}

//Machine states

void loop()
{
    switch (current_state)
    {
    case Start_Game:
        display_start_screen();

        if (StartPause_Toggle)
        {
            bool finished_game_screen_setup;
            if (setup_game_screen(finished_game_screen_setup)){
                current_state = Play_Game;
            }
        }
        break;
    case Play_Game:
        run_game();
        if (StartPause_Flag)
        {
            current_state = Pause_Game;
        }
        else if (not StartPause_Flag)
        {
            current_state = Play_Game;
        }

        if (Reset_Flag == true){
            current_state = Start_Game;
        }

        //Game status decides here

        if (Teensy_points == 4 || Player_points == 4)
        {
            current_state = End_Game;
        }
        break;
    case Pause_Game:
        update_score_board();
        if (StartPause_Flag)
        {
            current_state = Pause_Game;
        }
        else if (not StartPause_Flag)
        {
            setup_game_screen(NULL);
            current_state = Play_Game;
        }

        if(Reset_Flag == true){
            current_state = Start_Game;
        }

        break;
    case End_Game:
        display_end_screen();

        if (Reset_Flag){
            current_state = Start_Game;
        }
        break;
    default:
        
        break;
    }

    switch_bounce_handler();
    StartPause_Toggle = false; 
    Reset_Flag = false;
}