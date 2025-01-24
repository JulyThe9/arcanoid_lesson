vector<block_type> vector_data_block;
vector<sf::RectangleShape> vector_graphics_block;

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

    std::srand(std::time(0));

    int random1 = (std::rand() % block_amount) + 1;
    int random2 = (std::rand() % block_amount) + 1;
    int random3 = (std::rand() % block_amount) + 1;
    int random4 = (std::rand() % block_amount) + 1;
    int random5 = (std::rand() % block_amount) + 1;
    int random6 = (std::rand() % block_amount) + 1;
    int random7 = (std::rand() % block_amount) + 1;
    int random8 = (std::rand() % block_amount) + 1;

    for (int i = 0; i < block_amount; i++)
    {
        if(i == random1)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }

        }
        else if(i == random2)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random3)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random4)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random5)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random6)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random7)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
            }
        }
        else if(i == random8)
        {
            if(i % 2 == 0)
            {
                texture = texture_ice;
                texture_type = TEXTURE_TYPE_ICE;
                block_value = 10;
            }
            else
            {
                texture = texture_poison;
                texture_type = TEXTURE_TYPE_POISON;
                block_value = 20;
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

