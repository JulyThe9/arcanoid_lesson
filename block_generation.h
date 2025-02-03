#include <cassert>

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
    int max_special_block_amount = 12;

    std::srand(std::time(0));
    int same_checker = 0;


    //to generate the 12 random block numbers in order
    for (int i = 0; i < max_special_block_amount; i++)
    {
        int random_number = (std::rand() % block_amount) + 1;

        int vec_size = random_blocks.size();

        random_blocks.push_back(random_number);

        //if element at i is equal to a element at index same_checker the element at i gets popped back, runs as much as size of random_blocks big is in that iteration - 1
        for(int j = 0; j < vec_size; j++)
        {
            //checks if all indexes are in scope of the size of random_blocks
            assert(i < random_blocks.size());


            if (random_blocks[i] == random_blocks[same_checker])
            {
                random_blocks.pop_back();
                i--;
                same_checker = 0;
                break;
            }
            else
            {
                same_checker++;
            }
        }
    }

    for(int i = 0; i < random_blocks.size(); i++)
    {
        cout << random_blocks[i] << endl;
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
            currblockX = 160;
        }
        else
        {
            currblockX = prevblockX + block_WIDTH;
        }

        localblockX = currblockX;
        vector_data_block.push_back(block_type(block_WIDTH, block_LEN, localblockX, localblockY, texture, texture_type, block_value));
        prevblockX = currblockX;

        if((i + 1) % blocks_in_row == 0)
        {
            localblockX = 135;
            currblockX = 160;
            prevblockX = currblockX - block_WIDTH;
            localblockY += block_LEN;
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

