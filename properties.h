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
int block_WIDTH = 500;
int block_LEN = 200;
sf::RectangleShape block;

struct block_type
{
    //fields
    int block_width;
    int block_len;

    int blockX;
    int blockY;

    int top_bside;
    int left_bside;
    int right_bside;
    int bottom_bside;
    bool active;

    //constructor
    block_type(int block_widthPar, int block_lenPar, int blockXPar, int blockYPar)
    {
        block_width = block_widthPar;
        block_len = block_lenPar;
        blockX = blockXPar;
        blockY = blockYPar;
        top_bside = blockY;
        left_bside = blockX;
        right_bside =  blockX + block_width;
        bottom_bside = blockY + block_len;
        active = true;
    }
};
//instantiating an object of type block type
block_type main_block(block_WIDTH, block_LEN, screensizeX / 2 - block_WIDTH / 2, 200);

block_type secondary_block(block_LEN, block_LEN, 800, 700);

