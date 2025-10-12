void plat_movement(sf::RenderWindow &main_window)
{
    static bool mouse_reset_done = false;
    sf::Vector2i localPosition = sf::Mouse::getPosition(main_window);

    //X
    if(curr_gamestate.platform.x > left_wall)
    {
        curr_gamestate.platform.x = localPosition.x;
    }
    else
    {
        curr_gamestate.platform.x = left_wall;
    }

    if (curr_gamestate.platform.x + curr_gamestate.platform.width < right_wall)
    {
        curr_gamestate.platform.x = localPosition.x;
    }
    else
    {
        curr_gamestate.platform.x = right_wall - curr_gamestate.platform.width;
    }


    if (is_plat_y_axis_joker_active)
    {
        curr_gamestate.platform.width = curr_gamestate.platform.y / 7;
        if (!mouse_reset_done)
        {
            sf::Mouse::setPosition(sf::Vector2i(curr_gamestate.platform.x, curr_gamestate.platform.y), main_window);
            mouse_reset_done = true;
        }

        // Y
        if (curr_gamestate.platform.y > top_wall)
        {
            curr_gamestate.platform.y = localPosition.y;
        }
        else
        {
            curr_gamestate.platform.y = top_wall;
        }

        if (curr_gamestate.platform.y + curr_gamestate.platform.len < bottom_wall)
        {
            curr_gamestate.platform.y = localPosition.y;
        }
        else
        {
            curr_gamestate.platform.y = bottom_wall - curr_gamestate.platform.len;
        }
    }
    else
    {
        mouse_reset_done = false;
    }
}
