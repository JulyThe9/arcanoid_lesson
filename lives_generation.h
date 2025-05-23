/**
*@file lives_generation.h
*@brief logic to generates lives

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


sf::RectangleShape init_lives(lives_type current_life);

/**
*@brief sets data of hearts for graphics
*/
void set_life_data()
{
    int currlifeX = 0;
    int prevlifeX = 0;

    int x = 25;
    int y = 10;

    int width = 100;
    int length = 100;
    int spacing = 100;

    for(int i = 0; i < curr_gamestate.lives_amount; i++)
    {
        if(i == 0)
        {
            currlifeX = x;
        }
        else
        {
            currlifeX = prevlifeX + spacing;
        }

        x = currlifeX;

        vector_life_data.push_back(lives_type(x, y, width, length, spacing, heart_texture_full));

        prevlifeX = currlifeX;
    }
}


/**
*@brief calls initialization of heart for every life and adds it to vector_graphics_life(drawing called in main)
*/
int set_life_graphics()
{
    for (int i = 0; i < curr_gamestate.lives_amount; i++)
    {
        vector_graphics_life.push_back(init_heart(vector_life_data[i], i));
    }
    return 0;
}
