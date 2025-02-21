#include <cassert>
vector<block_type> vector_columns;
vector<sf::RectangleShape> vector_graphics_block;
vector<int> random_blocks;



sf::Texture curr_block_texture;
texture_types current_texture_type;
int current_block_value;


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

void generate_row(texture_types starterblock, int row_number, int &localblockX, int &localblockY)
{
    int currblockX = 0;
    int prevblockX = 0;


    for(int i = 0; i < block_columns; i++)
    {
        int random_number = (std::rand() % 100);
        if(random_number >= 85)
        {
            if(i % 2 == 0)
            {
                set_as_ice();
            }
            else
            {
                set_as_poison();
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
            currblockX = 160;
        }
        else
        {
            currblockX = prevblockX + block_WIDTH;
        }

        localblockX = currblockX;
        prevblockX = currblockX;

        vector_columns.push_back(block_type(block_WIDTH, block_LEN, localblockX, localblockY,
                                                curr_block_texture, current_block_value));
        if(i + 1 == block_columns)
        {
            currblockX = 160;
            localblockY += block_LEN;
        }
    }
}

int create_blocks_data()
{
    int localblockX = 0;
    int localblockY = 100;


    texture_types starter_texture = TEXTURE_TYPE_DIRT;

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
    cout << "size of data_vector: " << vector_columns.size() << endl;
    return 0;
}


int create_blocks_graphics()
{
    cout << "block_amount: " << block_amount << endl;
    cout << "blocks_in_row: " << block_columns << endl;
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            vector_graphics_block.push_back(init_block(curr_gamestate.blocks[i][j]));
        }
        curr_gamestate.blocks_graphics.push_back(vector_graphics_block);
        vector_graphics_block.clear();
    }
    cout << "size of graphic_vector: " << vector_graphics_block.size() << endl;
    return 0;
}

