#include <iostream>
#include <map>
#include <random>
#include <string>
#include <cmath>
#include <iomanip>
#include <variant>

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

#define BALL_SPEED 0.2

#define POWERUP_SPEED 400
#define POWERUP_WIDTH 30
#define POWERUP_LEN 30

#define TIMER_WIDTH 100
#define TIMER_HEIGHT 10

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



/*
enum powerup_effect_types
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
*/


enum powerup_buff_effect_types
{
    BALL_DUPLICATION,
    TRAJECTORY_PREDICTION,
    LAZER,
};


enum powerup_debuff_effect_types
{
    BALL_INVIS,
    REVERSE_CONTROLS,
    DIRECTION_RANDOMIZATION,
};


enum powerup_joker_effect_types
{
    PLAT_Y_AXIS,
    REMIX_BLOCK_GENERATION,
};


enum powerup_class_types
{
    JOKER,
    BUFF,
    DEBUFF,
};



std::map<double, powerup_buff_effect_types> buff_map =
{
    {25, BALL_DUPLICATION},
    {45, TRAJECTORY_PREDICTION},
    {50, LAZER}

};


std::map<double, powerup_debuff_effect_types> debuff_map =
{
    {17, BALL_INVIS},
    {16, REVERSE_CONTROLS},
    {15, DIRECTION_RANDOMIZATION}

};


std::map<double, powerup_joker_effect_types> joker_map =
{
    {14, PLAT_Y_AXIS},
    {13, REMIX_BLOCK_GENERATION}

};


std::map<double, powerup_class_types> powerup_class_map =
{
    {25, JOKER},
    {50, BUFF},
    {35, DEBUFF}
};


template <typename T>
T get_weighted_random(const std::map<double, T> &powerup_chances) {

    // temporary map to store the normalized values (because percentage values can add up to > 100)
    std::map<std::string, T> temp_map;

    T new_val;

    int total_weight = 0;
    double key = 0;

    // calculate total weight
    for (const auto& pair_elem : powerup_chances)
    {
        total_weight += pair_elem.first;
    }

    // normalizing weights(adjust percentages based on 100%),
    // we assume that map keys represent a value between 0 and 100%
    for (const auto& pair_elem : powerup_chances)
    {
        // value normalization
        key = (pair_elem.first * 100) / total_weight;

        // to make sure that the keys are correctly formatted -
        // for accessing values in the future we convert double in to string
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << key;
        std::string keystring = ss.str();

        // create new map entry with normalized values
        new_val = pair_elem.second;
        temp_map[keystring] = new_val;
    }

    // fancy way of getting a number between 0 and 100
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // we use 100 because we have normalized the weights
    std::uniform_real_distribution<> dis(0, 100);


    // place the random number into 'r'
    double r_temp = dis(gen);

    // round down r (in cases when double is 99.999)
    double r = static_cast<int>(std::floor(r_temp));

    // for calculating normalized weight intervals
    double upto = 0;
    double weight = 0;

    for (const auto& pair_elem : temp_map)
    {
        weight = std::stod(pair_elem.first);  // convert string key back to double
        upto += weight;
        if (r < upto)
            return pair_elem.second;  // return this powerup
    }
    // this should never happen
    return powerup_chances.begin()->second;
}

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

/*
powerup_effect_types get_powerup_effect(powerup_status type)
{
    int random_number = (std::rand() % 100);

    if(type == BUFF_POWERUP)
    {
        if (random_number <= 34)
            return BALL_DUPLICATION;
        else if (random_number <= 67)
            return TRAJECTORY_PREDICTION;
        else
            return LAZER;
    }
    else if(type == DEBUFF_POWERUP)
    {
        if (random_number <= 34)
            return BALL_INVIS;
        else if (random_number <= 67)
            return REVERSE_CONTROLS;
        else
            return DIRECTION_RANDOMIZATION;
    }
    else
    {
        if (random_number <= 50)
            return PLAT_Y_AXIS;
        else
            return REMIX_BLOCK_GENERATION;
    }

}
*/


sf::RectangleShape init_powerup(powerup_class_types type, int x, int y);


struct falling_powerup_type
{
    bool powerup_active;
    bool first_activation;

    float x;
    float y;
    sf::Clock powerup_clock;
    float powerupSpeed;

    sf::RectangleShape rectangle;
    sf::Texture texture;

    powerup_class_types type;
    std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> powerup_effect;

    int chance_of_appearence;


    falling_powerup_type(int xpar, int ypar, float powerupSpeedpar, block_type &blockpar, powerup_class_types typepar)
    {
        x = xpar;
        y = ypar;
        powerup_active = false;
        first_activation = true;
        powerupSpeed = powerupSpeedpar;
        type = typepar;

        if (type == BUFF)
            powerup_effect = get_weighted_random(buff_map);
        else if (type == DEBUFF)
            powerup_effect = get_weighted_random(debuff_map);
        else
            powerup_effect = get_weighted_random(joker_map);

        rectangle = init_powerup(typepar, xpar, ypar);
    }
};

sf::RectangleShape init_timer_graphic(powerup_class_types type);

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

    std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> powerup_effect;

    timer_type(int xpar, int ypar, powerup_class_types typepar, std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> powerup_effectpar)
    {
        len = TIMER_HEIGHT;
        width = TIMER_WIDTH;
        x = xpar;
        y = ypar;
        timer_active = false;
        graphic = init_timer_graphic(typepar);
        graphic.setPosition(x, y);
        powerup_effect = powerup_effectpar;
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

vector<falling_powerup_type> falling_powerups;
vector<timer_type> cooldown_bars;


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
