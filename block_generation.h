vector<block_type> vector_data_block;
vector<sf::RectangleShape> vector_graphics_block;

//instantiation
int currblockX = 0;
int prevblockX = 0;

//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type &current_block);


int create_blocks_data()
{
    sf::Texture texture;
    texture_types texture_type;
    int localblockX = 0;
    int localblockY = 100;
    int block_value;


    for (int i = 0; i < block_amount; i++)
    {
        if(i % 3 == 0)
        {
            texture = texture_ice;
            texture_type = TEXTURE_TYPE_ICE;
            block_value = 10;
        }
        else if (i % 3 == 1)
        {
            texture = texture_poison;
            texture_type = TEXTURE_TYPE_POISON;
            block_value = 20;
        }
        else
        {
            texture = texture_dirt;
            texture_type = TEXTURE_TYPE_DIRT;
            block_value = 5;
        }

        if(i == 0)
        {
            currblockX = 135;
        }
        else
        {
            currblockX = prevblockX + block_WIDTH + block_spacing;
        }


        localblockX = currblockX;
        vector_data_block.push_back(block_type(block_WIDTH, block_LEN, localblockX, localblockY, texture, texture_type, block_value));
        prevblockX = currblockX;

        if((i + 1) % blocks_in_row == 0)
        {
            localblockX = 135;
            currblockX = 135;
            prevblockX = currblockX - block_WIDTH - block_spacing;
            localblockY += block_LEN + 5;
        }
    }
    return 0;
}


int create_blocks_graphics()
{
    for (int i = 0; i < block_amount; i++)
    {
        //init block call
        vector_graphics_block.push_back(init_block(vector_data_block[i]));
    }
    return 0;
}

