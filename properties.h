using namespace std;


//----
//BALL
//----
float ball_speed = 3;
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
//80/30 is good
int block_WIDTH = 10;
int block_LEN = 3;

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

vector<block_type> vector_data;
vector<sf::RectangleShape> vector_graphics;

//instantiation
int currX = 0;
int prevX = 0;
int block_amount = 5000;

//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type current_block);



int create_blocks_data()
{
    int localposX = 0;
    int localposY = 200;

    for (int i = 0; i < block_amount; i++)
    {
        cout <<"i: " <<  i << ", X: " << localposX << ", Y: "<< localposY << endl;

        currX = prevX + block_WIDTH + 2;
        localposX = currX;
        vector_data.push_back(block_type(block_WIDTH, block_LEN, localposX, localposY));
        prevX = currX;
        cout << "INSIDE MULT_BLOCK; " << "posX: " << vector_data[i].blockX << "; posY: " << vector_data[i].blockY << endl;
        if((i + 1) % 85 == 0)
        {
            localposX = 0;
            currX = 0;
            prevX = 0;
            localposY += block_LEN + 5;
        }
    }
    return 0;
}



int create_blocks_graphics()
{
    for (int i = 0; i < block_amount; i++)
    {
        vector_graphics.push_back(init_block(vector_data[i]));
    }
    return 0;
}
