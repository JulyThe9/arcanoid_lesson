#include <cassert>

vector<block_type> vector_data_block;
vector<sf::RectangleShape> vector_graphics_block;
vector<int> random_blocks;


//instantiation
int currblockX = 0;
int prevblockX = 0;


//forward declaration: tells compiler "all good I have this covered"
sf::RectangleShape init_block(block_type &current_block);

void set_as_dirt1()
{
    texture = texture_dirt;
    texture_type = TEXTURE_TYPE_DIRT;
    block_value = 1;
}

void set_as_dirt2()
{
    texture = texture_dirt2;
    texture_type = TEXTURE_TYPE_DIRT2;
    block_value = 5;
}


void generate_rows(texture_types starterblock, int row_number)
{
    //i is current block index
    for(int i = 0; i < blocks_in_row; i++)
    {
        //checks if any randomly generated number is equal to the number of current block(i)
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
        //this case is for even blocks for example: 0, 2, 4, ...
        //our first block is in here so startertexture applies for it
        else if(i % 2 == 0)
        {
            //if our startertexture is dirt1 we set it accordingly,
            //if its dirt2, we set it to the other values corresponding to dirt2
            if(starter_texture == TEXTURE_TYPE_DIRT)
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
            if(starter_texture == TEXTURE_TYPE_DIRT)
            {
                set_as_dirt2();
            }
            //If we start with dirt 2, we alternate with dirt1
            else
            {
                set_as_dirt1();
            }
        }
    }
}

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

    texture_type starter_texture;
    texture_type alter_texture;

    //to generate the 12 random block numbers in order
    for (int i = 0; i < max_special_block_amount; i++)
    {
        int random_number = (std::rand() % block_amount) + 1;

        int vec_size = random_blocks.size();

        random_blocks.push_back(random_number);

        //if element at i is equal to a element at index same_checker the element at i gets popped back, runs as much as size of random_blocks big is in that iteration - 1
        for(int j = 0; j < vec_size; j++)
        {
            //checks if i are in scope of the size of random_blocks
            //assert means if its true, it continues code, if its false it stops code and gives you the line of error
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

    std::sort(random_blocks.begin(), random_blocks.end());

    for (int curr_row_number = 0; curr_row_number < block_rows; i++)
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

        generate_rows(starter_texture, curr_row_number);





        /*
        if(curr_row_number == 0)
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

        if((curr_row_number + 1) % blocks_in_row == 0)
        {
            localblockX = 135;
            currblockX = 160;
            prevblockX = currblockX - block_WIDTH;
            localblockY += block_LEN;

            if(row_num % 2 == 0)
            {
                cout << "we are on row: " << row_num << endl;
            }
        }
        */
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

