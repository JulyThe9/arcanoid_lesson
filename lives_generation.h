vector<lives_type> vector_life_data;
vector<sf::RectangleShape> vector_graphics_life;

int currlifeX = 0;
int prevlifeX = 0;


//forward decleration
sf::RectangleShape init_lives(lives_type current_life);



int set_life_data()
{
    int colour_red;
    int colour_green;
    int colour_blue;

    int locallifeX = screensizeX - 150;
    int locallifeY = screensizeY - 100;

    for(int i = 0; i < lives_amount; i++)
    {
        if(i == 0)
        {
            colour_red = 100;
            colour_green = 250;
            colour_blue = 50;
        }
        else if(i == 1)
        {
            colour_red = 255;
            colour_green = 255;
            colour_blue = 0;
        }
        else
        {
            colour_red = 255;
            colour_green = 0;
            colour_blue = 0;
        }
        if(i == 0)
        {
            currlifeX = locallifeX;
        }
        else
        {
            currlifeX = prevlifeX + life_width + lives_spacing;
        }

        locallifeX = currlifeX;

        vector_life_data.push_back(lives_type(life_width, life_length, locallifeX, locallifeY, lives_amount,  colour_red, colour_green, colour_blue));

        prevlifeX = currlifeX;
    }
    return 0;
}


int set_life_graphics()
{
    for (int i = 0; i < lives_amount; i++)
    {
        //init life call
        vector_graphics_life.push_back(init_lives(vector_life_data[i]));
    }
    return 0;
}

