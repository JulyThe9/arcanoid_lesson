/**
*@file properties.h
*@brief contains all objects, all defines, all enums and most global variables

*@author [Johannes Waldeck]
*@date [28.04.2025]
*/


using namespace std;

// GLOBAL DEFINES
#define TEXT_VISIBLE_PERIOD 750
#define TEXT_NOT_VISIBLE_PERIOD 750

#define SCREENSIZE_X 1500
#define SCREENSIZE_Y 1200

#define BALL_STARTER_DEG 30

#define BLOCK_LEN 30
#define BLOCK_WIDTH 90

#define BALL_SPEED 0.34

#define POWERUP_SPEED 400
#define POWERUP_WID 30
#define POWERUP_LEN 30

#define TIMER_WIDTH 100
#define TIMER_LEN 10

//#define DEBUG
//-------------------------------------------------------------------

bool text_visible = false;

const double PLATFORM_INITIAL_Y = SCREENSIZE_Y - 120;

const int BALL_START_POSX = SCREENSIZE_X / 2;
const int BALL_START_POSY = SCREENSIZE_Y / 2 + 100;


//--------
// WALLS
//--------
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
float godspeed = 0.8;

//--------
// SOUNDS
//--------
sf::SoundBuffer buffer_dirt;
sf::Sound sound_dirt;
sf::SoundBuffer buffer_ice;
sf::Sound sound_ice;
sf::SoundBuffer buffer_poison;
sf::Sound sound_poison;
sf::SoundBuffer buffer_explosion;
sf::Sound sound_explosion;
sf::SoundBuffer buffer_wall;
sf::Sound sound_wall;
sf::SoundBuffer buffer_platform;
sf::Sound sound_platform;
sf::Sound current_sound;
sf::SoundBuffer current_buffer;

sf::Music music;

sf::RectangleShape powerup;
sf::RectangleShape timer;


//--------
// BLOCK TEXTURES
//--------
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

int status_bar_width = SCREENSIZE_X;
int status_bar_length = 120;

bool game_active = true;

//--------
// GAME STATUS TEXTS
//--------
sf::Text heart_deduction_text;
sf::Text no_hearts_text;
sf::Text game_won_text;

//-------------------------------------------------------------------
/**
*@enum all collision_cases

*@var COLLISION_CASE_BOTTOM
* hit bottom surface
*@var COLLISION_CASE_TOP
* hit top surface
*@var COLLISION_CASE_LEFT
* hit left surface
*@var COLLISION_CASE_RIGHT
* hit right surface
*@var COLLISION_CASE_PLATFORM_RIGHT
* hit right surface of platform
*@var COLLISION_CASE_PLATFORM_LEFT
* hit left surface of platform
*@var COLLISION_CASE_RESET
* reset everything to beginning after ball hit barrier
*/
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

/**
*@enum block_texture_types

*@var TEXTURE_TYPE_ICE
* texture of ice
*@var TEXTURE_TYPE_POISON
* texture of poison
*@var TEXTURE_TYPE_DIRT
* texture of dirt
*@var TEXTURE_TYPE_DIRT2
* texture of second dirt
*@var TEXTURE_TYPE_EXPLOSION_SMALL
* texture of small explosion
*@var TEXTURE_TYPE_EXPLOSION_LARGE
* texture of large explosion
*/
enum block_texture_types
{
    TEXTURE_TYPE_ICE,
    TEXTURE_TYPE_POISON,
    TEXTURE_TYPE_DIRT,
    TEXTURE_TYPE_DIRT2,
    TEXTURE_TYPE_EXPLOSION_SMALL,
    TEXTURE_TYPE_EXPLOSION_LARGE,
};

/**
*@enum game_status_type

*@var GAME_ACTIVE
* gamestate is active
*@var HEART_DEDUCTION
* gamestate in heart deduction
*@var HEARTS_GONE
* gamestate in game loss
*@var BLOCKS_GONE
* gamestate in game won
*/
enum game_status_type
{
    GAME_ACTIVE,
    HEART_DEDUCTION,
    HEARTS_GONE,
    BLOCKS_GONE,
};

enum sound_type
{
    DIRT_SOUND,
    ICE_SOUND,
    POISON_SOUND,
    EXPLOSION_SOUND,
    WALL_SOUND,
    PLATFORM_SOUND,
};

enum powerup_status
{
    JOKER_POWERUP,
    DEBUFF_POWERUP,
    BUFF_POWERUP,
};

enum diff_powerups
{
    //BUFFS
    BALL_DUPLICATION,
    TRAJECTORY_PREDICTION,
    LAZER,
    //DEBUFFS
    BALL_INVIS,
    REVERSE_CONTROLS,
    DIRECTION_RANDOMIZATION,
    //JOKERS
    PLAT_Y_AXIS,
    REMIX_BLOCK_GENERATION,
};

//-------------------------------------------------------------------


/**
*@brief a struct representing the block_type blocks logic
*/
//--------
//used for collisions and block related data (!not used for textures!)
//--------
struct block_type
{
    int blockX;
    int blockY;

    int top_bside;
    int left_bside;
    int right_bside;
    int bottom_bside;
    //if a block is still active(able to collide with ball and still visible) or not active
    bool active;
    sf::Texture texture;
    block_texture_types texturetype;
    int block_value;
    //explosion radius to check if its large explosion radius(true) or small explosion radius(false), used in hit_block()
    bool radius;
    sound_type block_sound;

    block_type(int blockXPar, int blockYPar, sf::Texture texturepar, block_texture_types texturetypepar, int block_valuepar, bool radiuspar, sound_type block_soundpar)
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
        //value of score points a block type has
        block_value = block_valuepar;
        radius = radiuspar;
        block_sound = block_soundpar;
    }
};


sf::RectangleShape init_powerup(block_type &current_block, powerup_status type);


struct powerup_type
{
    bool powerup_active;
    bool first_activation;

    float x;
    float y;
    sf::Clock powerup_clock;
    float powerupSpeed;
    sf::RectangleShape graphic;
    powerup_status type;


    powerup_type(int xpar, int ypar, float powerupSpeedpar, block_type &blockpar, powerup_status typepar)
    {
        x = xpar;
        y = ypar;
        powerup_active = false;
        first_activation = true;
        powerupSpeed = powerupSpeedpar;
        graphic = init_powerup(blockpar, typepar);
        type = typepar;
    }
};

sf::RectangleShape init_timer_graphic(powerup_status type);

struct timer_type
{
    int len;
    int width;

    float x;
    float y;

    bool timer_active;

    sf::Clock powerup_clock;
    sf::RectangleShape graphic;

    float duration = 15;

    diff_powerups specific_powerup;

    timer_type(int xpar, int ypar, powerup_status typepar, diff_powerups specific_poweruppar)
    {
        len = TIMER_LEN;
        width = TIMER_WIDTH;
        x = xpar;
        y = ypar;
        timer_active = false;
        graphic = init_timer_graphic(typepar);
        graphic.setPosition(x, y);
        specific_powerup = specific_poweruppar;
    }
};

/**
*@brief a struct representing the platform_type platform logic
*/
struct platform_type
{
    float x;
    float y;

    int width;
    int len;

    int plat_speed;

    //used in get_new_angle() for sections of platform in each half to calculate new ball angle
    int reflection_steps;

    float platform_starter_x;

    platform_type(){};

    platform_type(float ypar, int widthpar, int lenpar, int plat_speedpar, int reflection_stepspar)
    {
        platform_starter_x = SCREENSIZE_X / 2 - widthpar / 2 + (35 * 4) + 156;

        x = platform_starter_x;
        y = ypar;

        width = widthpar;
        len = lenpar;

        plat_speed = plat_speedpar;

        reflection_steps = reflection_stepspar;
    }

};



/**
*@brief a struct representing the ball_type ball logic
*/
struct ball_type
{
    float speed;
    int size_radius;

    // current ball position at each frame
    float curr_x;
    float curr_y;

    // ball position after every collision or beginning (recent ball position)
    float recent_x;
    float recent_y;

    ball_type(){};

    ball_type(float speedpar, int size_radiuspar, float curr_xpar, float curr_ypar, float recent_xpar, float recent_ypar)
    {
        speed = speedpar;
        size_radius = size_radiuspar;
        curr_x = curr_xpar;
        curr_y = curr_ypar;
        recent_x = recent_xpar;
        recent_y = recent_ypar;
    }
};


/**
*@brief a struct representing the current gamestate
*/
struct GameState
{
    bool isInitialized = false;

    string score_number;

    vector<vector<block_type>> blocks;

    vector<vector<sf::RectangleShape>> blocks_graphics;

    int lives_amount;
    int block_amount;

    ball_type ball;
    platform_type platform;


    GameState()
    {
        //needs to be initialized before objects, because Gamestate is necessary for objects
        //added assert in to main in case object exists with empty values
        isInitialized = false;
    };

    void init(string score_numberpar, int lives_amountpar, int block_amountpar, ball_type ballpar, platform_type platformpar)
    {
        score_number = score_numberpar;
        lives_amount = lives_amountpar;
        block_amount = block_amountpar;
        ball = ballpar;
        platform = platformpar;
        isInitialized = true;
    }
};


/**
*@brief a struct representing the lives_type current life
*/
struct lives_type
{
    int x;
    int y;

    int width;
    int length;
    int spacing;

    sf::Texture texture;

    lives_type(int xpar, int ypar,  int widthpar, int lengthpar, int spacingpar, sf::Texture texturepar)
    {
        x = xpar;
        y = ypar;

        width = widthpar;
        length = lengthpar;

        spacing = spacingpar;
        texture = texturepar;
    }
};

vector<lives_type> vector_life_data;
vector<sf::RectangleShape> vector_graphics_life;


/**
*@brief a struct representing the logo_type game logo
*/
struct logo_type
{
    int width;
    int length;

    int x;
    int y;

    logo_type(int widthpar, int lengthpar, int xpar, int ypar)
    {
        width = widthpar;
        length = lengthpar;

        x = xpar;
        y = ypar;
    }
};


/**
*@brief a struct representing the barrier_type barrier
*/
struct barrier_type
{
    int x;
    int y;

    int width;
    int length;

    barrier_type(int xpar, int ypar,  int widthpar, int lengthpar)
    {
        x = xpar;
        y = ypar;

        width = widthpar;
        length = lengthpar;
    }
};


//-------------------------------------------------------------------
int block_rows = (SCREENSIZE_Y - (PLATFORM_INITIAL_Y / 1.2)) / BLOCK_LEN;
int block_columns = (SCREENSIZE_X - 2 * BLOCK_WIDTH) / BLOCK_WIDTH - 1;

GameState curr_gamestate;

vector<powerup_type> powerups;
vector<timer_type> timers;


/**
*@brief initializes GameState(called in main)
*/
void init_gamestate()
{
    ball_type ball_data(BALL_SPEED, 10, BALL_START_POSX, BALL_START_POSY, BALL_START_POSX, BALL_START_POSY);
    platform_type platform(PLATFORM_INITIAL_Y, 160, 12, 45, 25);
    curr_gamestate.init("000000", 3, block_rows * block_columns, ball_data, platform);
}

logo_type logo(300, 109, SCREENSIZE_X / 3 + 100, 0);

int barrier_len = 10;
barrier_type barrier_obj(0, SCREENSIZE_Y - barrier_len - 5, SCREENSIZE_X, barrier_len);

//GAME STATUS
game_status_type game_status = GAME_ACTIVE;

collision_cases last_collision = COLLISION_CASE_RESET;
