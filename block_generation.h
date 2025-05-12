/**
*@file block_generation.h
*@brief all logic to generate blocks in correct order

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/

/**
*@brief initialization of platform
*/

#include <cassert>
vector<block_type> vector_columns;
vector<sf::RectangleShape> vector_graphics_block;
vector<int> random_blocks;


sf::Texture curr_block_texture;
block_texture_types current_texture_type;
int current_block_value;
bool radius;
sound_type block_sound;


//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type &current_block);

/**
*@brief sets current block texture related fields to dirt1
*/
void set_as_dirt1()
{
    curr_block_texture = texture_dirt;
    current_texture_type = TEXTURE_TYPE_DIRT;
    current_block_value = 1;
    block_sound = DIRT_SOUND;
}

/**
*@brief sets current block texture related fields to dirt2
*/
void set_as_dirt2()
{
    curr_block_texture = texture_dirt2;
    current_texture_type = TEXTURE_TYPE_DIRT2;
    current_block_value = 5;
    block_sound = DIRT_SOUND;
}

/**
*@brief sets current block texture related fields to ice
*/
void set_as_ice()
{
    curr_block_texture = texture_ice;
    current_texture_type = TEXTURE_TYPE_ICE;
    current_block_value = 10;
    block_sound = ICE_SOUND;
}

/**
*@brief sets current block texture related fields to poison
*/
void set_as_poison()
{
    curr_block_texture = texture_poison;
    current_texture_type = TEXTURE_TYPE_POISON;
    current_block_value = 20;
    block_sound = POISON_SOUND;
}

/**
*@brief sets current block texture related fields to small explosion
*/
void set_as_explosion()
{
    curr_block_texture = texture_explosion_small;
    current_texture_type = TEXTURE_TYPE_EXPLOSION_SMALL;
    current_block_value = 1;
    radius = false;
    block_sound = EXPLOSION_SOUND;

}

/**
*@brief sets current block texture related fields to large explosion
*/
void set_as_explosion_large()
{
    curr_block_texture = texture_explosion_large;
    current_texture_type = TEXTURE_TYPE_EXPLOSION_LARGE;
    current_block_value = 2;
    radius = true;
    block_sound = EXPLOSION_SOUND;
}

/**
*@brief generates current row

*generates current row to current row position and dirt starterblock

*@param starterblock the dirt type of starterblock in row
*@param localblockX the x-position of the first block in current row
*@param localblockY the y-position of the first block in current row
*/
void generate_row(block_texture_types starterblock, int &localblockX, int &localblockY)
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
            if(random_block_type > 65)
            {
                set_as_explosion();
            }
            else if(random_block_type > 45)
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
                                                curr_block_texture, current_texture_type, current_block_value, radius, block_sound));
        if(i + 1 == block_columns)
        {
            localblockY += BLOCK_LEN;
        }
    }
}


/**
*@brief creates data of all blocks for graphics and generation of each block
*/
void create_blocks_data()
{
    int localblockX = 0;
    int localblockY = 300;

    block_texture_types starter_texture = TEXTURE_TYPE_DIRT;

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

        generate_row(starter_texture, localblockX, localblockY);
        curr_gamestate.blocks.push_back(vector_columns);

        vector_columns.clear();
    }
}

/**
*@brief call initialization of each block by row and col(drawing called in main)
*/
void create_blocks_graphics()
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
}


sf::SoundBuffer map_sounds(sound_type block_sound)
{
    if(block_sound == DIRT_SOUND)
    {
        return buffer_dirt;
    }
    else if(block_sound == ICE_SOUND)
    {
        return buffer_ice;
    }
    else if(block_sound == POISON_SOUND)
    {
        return buffer_poison;
    }
    else if(block_sound == EXPLOSION_SOUND)
    {
        return buffer_explosion;
    }
}
