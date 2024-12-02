using namespace std;


//----
//BALL
//----
float ball_speed = 0.09;
int ball_size = 10;

// current ball position
float recent_posX = 500;
float recent_posY = 500;

//current ball position variable
float curret_posX = recent_posX;
float current_posY = recent_posY;

// size of screen
float screensizeX = 1500;
float screensizeY = 1000;

// walls
float right_wall = screensizeX;
float left_wall = 0;

float top_wall = 0;
float bottom_wall = screensizeY;

// angle of flight
float curr_degrees = -90;

float temp_y = 0;
float temp_x = 0;

float alpha_x = 0;
float alpha_y = 0;

// Create the main window
sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

//---------
//PLATFORM
//---------

int plat_speed = 60;

int plat_width = 300;
int plat_len = 12;

float platX = screensizeX / 2 - plat_width / 2 - 150;
float platY = 800;

float curr_platX = platX;
float curr_platY = platY;       //to calculate degrees for curr_degrees and not move the platform

float rest = 0;

//---------
//BLOCKS
//---------
//80/30 is good
int block_rows = 10;
int block_spacing = 5;
int block_LEN = 30;
int block_WIDTH = 90;
int blocks_in_row = (screensizeX - 2 * block_WIDTH) / (block_WIDTH + block_spacing);
int block_amount = blocks_in_row * block_rows;



struct block_type
{
    //fields
    int block_width;
    int block_len;

    int blockX;
    int blockX_new;
    int blockY;

    int top_bside;
    int left_bside;
    int right_bside;
    int bottom_bside;
    bool active;
    int colour_red_block;
    int colour_green_block;
    int colour_blue_block;

    //constructor
    block_type(int block_widthPar, int block_lenPar, int blockXPar, int blockYPar, int colour_redPar, int colour_greenPar, int colour_bluePar)
    {
        //size of block
        block_width = block_widthPar;
        block_len = block_lenPar;
        //position of block
        blockX = blockXPar;
        blockY = blockYPar;
        //colour of block
        colour_red_block = colour_redPar;
        colour_green_block = colour_greenPar;
        colour_blue_block = colour_bluePar;

        //sides of block
        top_bside = blockY;
        left_bside = blockX;
        right_bside =  blockX + block_width;
        bottom_bside = blockY + block_len;
        //block existant or not
        active = true;
        blockX_new = blockXPar;
    }
};

//--------
//BARRIAR
//--------

//size
int barrier_width = screensizeX;
int barrier_length = 10;

//positions
int barrierX = 0;
int barrierY = screensizeY - barrier_length - 5;

//--------
//LIVES
//--------

int life_width = 15;
int life_length = 70;
int lives_amount = 3;
int lives_spacing = life_width;
bool skip_blinking = false;
int step = 25;


struct lives_type
{
    int lives_width;
    int lives_length;
    int livesX;
    int livesY;
    int lives_num;
    int colour_red_life;
    int colour_green_life;
    int colour_blue_life;

    lives_type(int lives_widthPar, int lives_lengthPar, int livesXPar, int livesYPar, int lives_numPar,
               int colour_red_lifePar, int colour_green_lifePar, int colour_blue_lifePar)
    {
        lives_width = lives_widthPar;
        lives_length = lives_lengthPar;
        livesX = livesXPar;
        livesY = livesYPar;
        lives_num = livesXPar;
        colour_red_life = colour_red_lifePar;
        colour_green_life = colour_green_lifePar;
        colour_blue_life = colour_blue_lifePar;
    }
};
