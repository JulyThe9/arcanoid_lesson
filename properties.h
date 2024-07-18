using namespace std;

//----
//BALL
//----
float ball_speed = 5;
int plat_speed = 60;
int ball_size = 10;
int plat_width = 100;
int plat_len = 12;

// current ball position
float ballX = 500;
float ballY = 500;

//current ball position variable
float ballX2 = ballX;
float ballY2 = ballY;

// size of screen
float screensizeX = 1000;
float screensizeY = 1000;

// walls
float right_wall = screensizeX;
float left_wall = 0;

float top_wall = 0;
float bottom_wall = screensizeY;

// angle of flight
float curr_degrees = 30;

float temp_y = 0;
float temp_x = 0;

float alpha_x = 0;
float alpha_y = 0;


// remember wall
float last_wall = 0;

//---------
//RECTANGLE
//---------

float platX = 450;
float platY = 800;

float rest = 0;
