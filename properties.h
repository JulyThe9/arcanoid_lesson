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
int block_WIDTH = 80;
int block_LEN = 30;
sf::RectangleShape block;

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

    //constructor
    block_type(int block_widthPar, int block_lenPar, int blockXPar, int blockYPar)
    {
        //size of block
        block_width = block_widthPar;
        block_len = block_lenPar;
        //position of block
        blockX = blockXPar;
        blockY = blockYPar;
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

vector<block_type> vect1;

//instantiation
int currX = 0;
int prevX = 0;
//block_type main_block(block_WIDTH, block_LEN, 0, 200);

//forward declaration: tells compiler "all good I have this covered"
void init_block(block_type current_block);


int mult_block()
{
    int localposX = 0;
    int localposY = 200;



    for (int i = 0; i < 15; i++)
    {
        currX = prevX + block_WIDTH + 10;
        localposX = currX;
        vect1.push_back(block_type(block_WIDTH, block_LEN, localposX, localposY));
        prevX = currX;
        cout << "INSIDE MULT_BLOCK; " << "posX: " << vect1[i].blockX << "; posY: " << vect1[i].blockY << endl;
    }
    return 0;
}
