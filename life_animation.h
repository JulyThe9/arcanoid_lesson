int block_disappear()
{
    int colour_red;
    int colour_green;
    int colour_blue;

    int colour_red2 = 0;
    int colour_green2 = 0;
    int colour_blue2 = 0;

    int locallifeX = SCREENSIZE_X - 150;
    int locallifeY = SCREENSIZE_Y - 100;

    lives_type life_data2 = lives_type(life_width, life_length, locallifeX, locallifeY, lives_amount,  colour_red2, colour_green2, colour_blue2);
    sf::RectangleShape no_life = init_lives(life_data2);

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
        if(skip_blinking == false)
        {
            for (int i = 0; i < step; i++)
            {
                if(i == 24)
                {
                    skip_blinking = true;
                }
                if(i % 2 == 0)
                {
                    colour_green = (colour_green / step) * (step - 1);
                    lives_type life_data = lives_type(life_width, life_length, locallifeX, locallifeY, lives_amount,  colour_red, colour_green, colour_blue);
                    sf::RectangleShape life = init_lives(life_data);
                    app.draw(life);
                }
                else
                {
                    app.draw(no_life);
                }
                // Pause the loop for 1 second
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                // Update the window
                app.display();
                // Clear screen
                app.clear();
            }
        }
    }
    return 0;
}


