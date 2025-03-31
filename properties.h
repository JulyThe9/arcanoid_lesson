using namespace std;

// GLOBAL DEFINES
#define TEXT_VISIBLE_PERIOD 550
#define TEXT_NOT_VISIBLE_PERIOD 200

#define SCREENSIZE_X 1500
#define SCREENSIZE_Y 1200

#define BALL_STARTER_DEG 30

#define BLOCK_LEN 30
#define BLOCK_WIDTH 90

bool textVisible = false;

int ball_size = 10;

const int BALL_START_POSX = SCREENSIZE_X / 2;
const int BALL_START_POSY = SCREENSIZE_Y / 2 + 100;

// current ball position at each frame
float current_posX = BALL_START_POSX;
float current_posY = BALL_START_POSY;

// ball position after every collision or beginning
float recent_collisionX = current_posX;
float recent_collisionY = current_posY;

// walls
float right_wall = SCREENSIZE_X;
float left_wall = 0;
float top_wall = 0;
float bottom_wall = SCREENSIZE_Y;

// angle of flight(ball)
float curr_degrees = BALL_STARTER_DEG;

// direction +/- of flight
float alpha_x = 0;
float alpha_y = 0;

// godmode that makes you invinsible to barrier
bool godmode_active = false;
// active when true and block amount is under 4
bool crazy_ballspeed = true;
// godspeed if block amount are under 4 and ballspeed is true
float godspeed = 0.45;

//---------
// Barrier
//---------
int barrier_width = SCREENSIZE_X;
int barrier_length = 10;

int barrierX = 0;
int barrierY = SCREENSIZE_Y - barrier_length - 5;

//--------
// BLOCK TEXTURES
//--------
// 90/30 is good
sf::Texture texture_ice;
sf::Texture texture_poison;
sf::Texture texture_dirt;
sf::Texture texture_dirt2;
sf::Texture texture_explosion_small;
sf::Texture texture_explosion_large;

//--------
// STATUS BAR
//--------
sf::Texture background_status_bar;
sf::Texture arcanoid_logo;
sf::Texture heart_texture_full;
sf::Texture heart_texture_empty;
sf::Text score;
sf::Font font;

int logo_width = 300;
int logo_length = 109;

int logo_posX = (SCREENSIZE_X / 2) - (logo_width / 2);
int logo_posY = 0;

int status_bar_width = SCREENSIZE_X;
int status_bar_length = 120;

bool game_active = true;

//--------
// LIVES
//--------
int heart_width = 100;
int heart_length = 100;

int lives_amount = 3;
int lives_spacing = heart_width;
int step = 25;

//--------
// GAME STATUS TEXTS
//--------
sf::Text heart_deduction_text;
sf::Text no_hearts_text;
sf::Text game_won_text;


enum collision_cases
{
    COLLISION_CASE_BOTTOM,
    COLLISION_CASE_TOP,
    COLLISION_CASE_LEFT,
    COLLISION_CASE_RIGHT,
    COLLISION_CASE_PLATFORM_RIGHT,
    COLLISION_CASE_PLATFORM_LEFT,
    COLLISION_CASE_RESET,
};

enum texture_types
{
    TEXTURE_TYPE_ICE,
    TEXTURE_TYPE_POISON,
    TEXTURE_TYPE_DIRT,
    TEXTURE_TYPE_DIRT2,
    TEXTURE_TYPE_EXPLOSION_SMALL,
    TEXTURE_TYPE_EXPLOSION_LARGE,
};

enum game_status_type
{
    GAME_ACTIVE,
    HEART_DEDUCTION,
    HEARTS_GONE,
    BLOCKS_GONE,
};

struct block_type
{
    int blockX;
    int blockY;

    int top_bside;
    int left_bside;
    int right_bside;
    int bottom_bside;
    bool active;
    sf::Texture texture;
    texture_types texturetype;
    int block_value;
    bool radius;

    block_type(int blockXPar, int blockYPar, sf::Texture texturepar, texture_types texturetypepar, int block_valuepar, bool radiuspar)
    {
        blockX = blockXPar;
        blockY = blockYPar;

        texture = texturepar;
        texturetype = texturetypepar;

        //sides of block
        top_bside = blockY;
        left_bside = blockX;
        right_bside =  blockX + BLOCK_WIDTH;
        bottom_bside = blockY + BLOCK_LEN;

        //block existant or not
        active = true;
        block_value = block_valuepar;
        radius = radiuspar;
    }
};

struct GameState
{
    float ball_speed;

    int plat_speed;
    int plat_width;

    string score_number;

    vector<vector<block_type>> blocks;

    vector<vector<sf::RectangleShape>> blocks_graphics;

    int block_amount;

    GameState(float ball_speedpar, int plat_speedpar, int plat_widthpar, string score_numberpar, int block_amountpar)
    {
        ball_speed = ball_speedpar;
        plat_speed = plat_speedpar;
        plat_width = plat_widthpar;
        score_number = score_numberpar;
        block_amount = block_amountpar;
    }
};

struct lives_type
{
    int livesX;
    int livesY;
    int lives_num;
    sf::Texture heart_texture;


    lives_type(int livesXPar, int livesYPar, int lives_numPar, sf::Texture heart_texturepar)
    {
        livesX = livesXPar;
        livesY = livesYPar;
        lives_num = livesXPar;
        heart_texture = heart_texturepar;
    }
};



//--------
// PLATFORM
//--------
float platY = SCREENSIZE_Y - 120;
int block_rows = (SCREENSIZE_Y - (platY / 1.2)) / BLOCK_LEN;
int block_columns = (SCREENSIZE_X - 2 * BLOCK_WIDTH) / BLOCK_WIDTH - 1;
GameState curr_gamestate(0.24, 45, 200, "000000", block_rows * block_columns);
float platform_starter_X = SCREENSIZE_X / 2 - curr_gamestate.plat_width / 2 + (35 * 4);
float platX = platform_starter_X;
int plat_len = 12;



//GAME STATUS
game_status_type game_status = GAME_ACTIVE;
