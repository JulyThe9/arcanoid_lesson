vector<lives_type> vector_life_data;
vector<sf::RectangleShape> vector_graphics_life;

int currlifeX = 0;
int prevlifeX = 0;


//forward decleration
sf::RectangleShape init_lives(lives_type current_life);



int set_life_data()
{
    int locallifeX = 25;
    int locallifeY = 10;

    for(int i = 0; i < lives_amount; i++)
    {
        if(i == 0)
        {
            currlifeX = locallifeX;
        }
        else
        {
            currlifeX = prevlifeX + heart_width;
        }

        locallifeX = currlifeX;

        vector_life_data.push_back(lives_type(locallifeX, locallifeY, lives_amount));

        prevlifeX = currlifeX;
    }
    return 0;
}


int set_life_graphics()
{
    for (int i = 0; i < lives_amount; i++)
    {
        vector_graphics_life.push_back(init_heart(vector_life_data[i]));
    }
    return 0;
}

