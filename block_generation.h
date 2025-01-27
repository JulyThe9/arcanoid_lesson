vector<block_type> vector_data_block;
vector<sf::RectangleShape> vector_graphics_block;
vector<int> random_blocks;

//instantiation
int currblockX = 0;
int prevblockX = 0;

//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type &current_block);


int create_blocks_data()
{
    int localblockX = 0;
    int localblockY = 100;

    sf::Texture texture;
    texture_types texture_type;
    int block_value;

    int random_index = 0;
    int max_random_numbers = 12;

    std::srand(std::time(0));


    //to generate the 8 random numbers
    for (int i = 0; i < max_random_numbers; i++)
    {
        int random_number = (std::rand() % block_amount) + 1;
        random_blocks.push_back(random_number);
    }

    std::sort(random_blocks.begin(), random_blocks.end());

    for (int i = 0; i < block_amount; i++)
    {
        if(i == random_blocks[random_index])
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
                random_index++;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
                random_index++;
            }
        }
        else if(i % 2 == 0)
        {
            texture = texture_dirt2;
            texture_type = TEXTURE_TYPE_DIRT2;
            block_value = 1;
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

