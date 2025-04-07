#include <cassert>
vector<block_type> vector_columns;
vector<sf::RectangleShape> vector_graphics_block;
vector<int> random_blocks;


sf::Texture curr_block_texture;
texture_types current_texture_type;
int current_block_value;
bool radius;


//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type &current_block);

void set_as_dirt1()
{
    curr_block_texture = texture_dirt;
    current_texture_type = TEXTURE_TYPE_DIRT;
    current_block_value = 1;
}

void set_as_dirt2()
{
    curr_block_texture = texture_dirt2;
    current_texture_type = TEXTURE_TYPE_DIRT2;
    current_block_value = 5;
}

void set_as_ice()
{
    curr_block_texture = texture_ice;
    current_texture_type = TEXTURE_TYPE_ICE;
    current_block_value = 10;
}

void set_as_poison()
{
    curr_block_texture = texture_poison;
    current_texture_type = TEXTURE_TYPE_POISON;
    current_block_value = 20;
}

void set_as_explosion()
{
    curr_block_texture = texture_explosion_small;
    current_texture_type = TEXTURE_TYPE_EXPLOSION_SMALL;
    current_block_value = 1;
    radius = false;
}

void set_as_explosion_large()
{
    curr_block_texture = texture_explosion_large;
    current_texture_type = TEXTURE_TYPE_EXPLOSION_LARGE;
    current_block_value = 2;
    radius = true;
}

void generate_row(texture_types starterblock, int row_number, int &localblockX, int &localblockY)
{
    int currblockX = 0;
    int prevblockX = 0;

    if(block_columns * BLOCK_WIDTH > SCREENSIZE_X)
    {
        block_columns = (SCREENSIZE_X - 2 * BLOCK_WIDTH) / BLOCK_WIDTH + 1;
    }

    for(int i = 0; i < block_columns; i++)
    {

        int random_number = (std::rand() % 100);
        int random_block_type = (std::rand() % 100);
        if(random_number >= 60)
        {
            if(random_block_type > 100)
            {
                set_as_explosion();
            }
            else if(random_block_type > 100)
            {
                set_as_explosion_large();
            }
            else if(random_block_type > 20)
            {
                set_as_poison();
            }
            else if(random_block_type >= 0)
            {
                set_as_ice();
            }
        }
        //this case is for even blocks for example: 0, 2, 4, ...
        //our first block is in here so startertexture applies for it
        else if(i % 2 == 0)
        {
            //if our startertexture is dirt1 we set it accordingly,
            //if its dirt2, we set it to the other values corresponding to dirt2
            if(starterblock == TEXTURE_TYPE_DIRT)
            {
                set_as_dirt1();
            }
            else
            {
                set_as_dirt2();
            }
        }
        //this case is for odd blocks for example: 1, 3, 5, ...
        //this is my alternating section
        else
        {
            //if we start with dirt1, we alternate with dirt2
            if(starterblock == TEXTURE_TYPE_DIRT)
            {
                set_as_dirt2();
            }
            //If we start with dirt 2, we alternate with dirt1
            else
            {
                set_as_dirt1();
            }
        }


        if(i == 0)
        {
            currblockX = (SCREENSIZE_X - (BLOCK_WIDTH * block_columns)) / 2;
        }
        else
        {
            currblockX = prevblockX + BLOCK_WIDTH;
        }

        localblockX = currblockX;
        prevblockX = currblockX;


        vector_columns.push_back(block_type(localblockX, localblockY,
                                                curr_block_texture, current_texture_type, current_block_value, radius));
        if(i + 1 == block_columns)
        {
            localblockY += BLOCK_LEN;
        }
    }
}

int create_blocks_data()
{
    int localblockX = 0;
    int localblockY = 300;

    texture_types starter_texture = TEXTURE_TYPE_DIRT;

    if(block_rows * BLOCK_WIDTH > SCREENSIZE_X)
    {
        block_rows = (SCREENSIZE_Y - (curr_gamestate.platform.y/ 2)) / BLOCK_LEN;
    }

    for (int curr_row_number = 0; curr_row_number < block_rows; curr_row_number++)
    {
        //for even rows our first starter textures are dirt1, for odd rows startertexture is dirt2
        if(curr_row_number % 2 == 0)
        {
            starter_texture = TEXTURE_TYPE_DIRT;
        }
        else
        {
            starter_texture = TEXTURE_TYPE_DIRT2;
        }

        generate_row(starter_texture, curr_row_number, localblockX, localblockY);
        curr_gamestate.blocks.push_back(vector_columns);

        vector_columns.clear();
    }
    return 0;
}


int create_blocks_graphics()
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            vector_graphics_block.push_back(init_block(curr_gamestate.blocks[i][j]));
        }
        curr_gamestate.blocks_graphics.push_back(vector_graphics_block);
        vector_graphics_block.clear();
    }
    return 0;
}
