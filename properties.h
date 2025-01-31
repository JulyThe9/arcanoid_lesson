using namespace std;


//----
//BALL
//----
float ball_speed = 0.12;
int ball_size = 10;

// current ball position
//float recent_posX = 500;
//float recent_posY = 500;

float recent_posX = 5;
float recent_posY = 120;

//current ball position variable
float current_posX = recent_posX;
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
float curr_degrees = 30;

float temp_y = 0;
float temp_x = 0;

float alpha_x = 0;
float alpha_y = 0;

// Create the main window
sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

//---------
//PLATFORM
//---------

int plat_speed = 35;

int plat_width = 150;
int plat_len = 12;

float platX = screensizeX / 2 - plat_width / 2 - 150;
float platY = 800;

float curr_platX = platX;
float curr_platY = platY;       //to calculate degrees for curr_degrees and not move the platform

float rest = 0;

//---------
//BLOCKS
//---------
//90/30 is good
sf::Texture texture_ice;
sf::Texture texture_poison;
sf::Texture texture_dirt;
sf::Texture texture_dirt2;
int block_rows = 10;
int block_LEN = 30;
int block_WIDTH = 90;
int blocks_in_row = (screensizeX - 2 * block_WIDTH) / block_WIDTH;
int block_amount = blocks_in_row * block_rows;
double collision_margin = ball_speed + 0.0001;

enum texture_types
{
    TEXTURE_TYPE_ICE,
    TEXTURE_TYPE_POISON,
    TEXTURE_TYPE_DIRT,
    TEXTURE_TYPE_DIRT2,
};

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
    sf::Texture texture;
    int texture_type;
    int block_value;

    //constructor
    block_type(int block_widthPar, int block_lenPar, int blockXPar, int blockYPar, sf::Texture texturepar, int texture_typepar, int block_valuepar)
    {
        //size of block
        block_width = block_widthPar;
        block_len = block_lenPar;
        //position of block
        blockX = blockXPar;
        blockY = blockYPar;
        //colour of block
        texture = texturepar;
        //sides of block
        top_bside = blockY;
        left_bside = blockX;
        right_bside =  blockX + block_width;
        bottom_bside = blockY + block_len;
        //block existant or not
        active = true;
        blockX_new = blockXPar;
        texture_type = texture_typepar;
        block_value = block_valuepar;
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

//--------
//SCORE
//--------
sf::Text score;
sf::Font font;
string score_number = "0";


