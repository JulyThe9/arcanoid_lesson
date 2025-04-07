using namespace std;

// GLOBAL DEFINES
#define TEXT_VISIBLE_PERIOD 750
#define TEXT_NOT_VISIBLE_PERIOD 750

#define SCREENSIZE_X 1500
#define SCREENSIZE_Y 1200

#define BALL_STARTER_DEG 30

#define BLOCK_LEN 30
#define BLOCK_WIDTH 90

bool textVisible = false;

const double PLATFORM_INITIAL_Y = SCREENSIZE_Y - 120;

const int BALL_START_POSX = SCREENSIZE_X / 2;
const int BALL_START_POSY = SCREENSIZE_Y / 2 + 100;

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

int status_bar_width = SCREENSIZE_X;
int status_bar_length = 120;

bool game_active = true;


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

struct platform_type
{
    float x;
    float y;

    int width;
    int len;

    int plat_speed;

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
        isInitialized = false;
    };

    /*
    GameState(string score_numberpar, int lives_amountpar, int block_amountpar, ball_type ballpar, platform_type platformpar)
    {
        score_number = score_numberpar;
        lives_amount = lives_amountpar;
        block_amount = block_amountpar;
        ball = ballpar;
        platform = platformpar;
    }
    */

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


int block_rows = (SCREENSIZE_Y - (PLATFORM_INITIAL_Y / 1.2)) / BLOCK_LEN;
int block_columns = (SCREENSIZE_X - 2 * BLOCK_WIDTH) / BLOCK_WIDTH - 1;

GameState curr_gamestate;

void init_gamestate()
{
    ball_type ball_data(0.24, 10, BALL_START_POSX, BALL_START_POSY, BALL_START_POSX, BALL_START_POSY);
    platform_type platform(PLATFORM_INITIAL_Y, 200, 12, 45, 25);
    curr_gamestate.init("000000", 3, block_rows * block_columns, ball_data, platform);
}

logo_type logo(300, 109, (SCREENSIZE_X / 2) - (logo.width / 2), 0);

//GAME STATUS
game_status_type game_status = GAME_ACTIVE;

collision_cases last_collision = COLLISION_CASE_RESET;
