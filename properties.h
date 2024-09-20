using namespace std;

//----
//BALL
//----
float ball_speed = 0.06;
int ball_size = 10;

// current ball position
float recent_posX = 500;
float recent_posY = 500;

//current ball position variable
float curret_posX = recent_posX;
float current_posY = recent_posY;

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

//---------
//RECTANGLE
//---------

int plat_speed = 60;

int plat_width = 100;
int plat_len = 12;

float platX = screensizeX / 2 - plat_width / 2;
float platY = 800;

float rest = 0;

//---------
//BLOCKS
//---------

int block_width = 500;
int block_len = 250;

int blockX = screensizeX / 2 - block_width / 2;
int blockY = 200;

int top_bside = blockY;
int left_bside = blockX;
int right_bside = blockX + block_width;
int bottom_bside = blockY + block_len;
int i_frame = 0;



