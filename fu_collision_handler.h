// ---------------------------------
// WALL COLLISION DETECTION HERE
// ---------------------------------

void handle_collision_walls()
{
    if(temp_y >= bottom_wall - ball_size * 2)
        {
            handle_collision('b');
        }
        else if(temp_x >= right_wall - ball_size * 2)
        {
            handle_collision('r');
        }
        else if(temp_y <= top_wall)
        {
            handle_collision('t');
        }
        else if(temp_x <= left_wall)
        {
            handle_collision('l');
        }
}


// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_platform()
{
    if(temp_y + ball_size * 2 >= platY && temp_y + ball_size * 2 < platY + 0.1)
    {
        if(temp_x + ball_size * 2 > platX && temp_x < platX + plat_width)
        {
            handle_collision('b');
        }
    }
}

void hit_block()
{
    main_block.active = false;
}

// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    if(temp_y + ball_size * 2 >= main_block.top_bside && temp_y < main_block.top_bside + 0.1)
    {
        if(temp_x > main_block.blockX && temp_x < main_block.blockX + main_block.block_width)
        {
            if (main_block.active == true)
            {
                handle_collision('b');
                block.setFillColor(sf::Color(0, 0, 0));
                hit_block();
            }
        }
    }
    else if(temp_x + ball_size * 2 >= main_block.left_bside && temp_x < main_block.left_bside + 0.1)
    {
        if(temp_y > main_block.top_bside && temp_y < main_block.bottom_bside)
        {
            if (main_block.active == true)
            {
                handle_collision('r');
                block.setFillColor(sf::Color(0, 0, 0));
                hit_block();
            }
        }
    }
    else if(temp_y <= main_block.bottom_bside && temp_y > main_block.bottom_bside - 0.1)
    {
        if(temp_x > main_block.left_bside + ball_size && temp_x < main_block.right_bside)
        {
            if (main_block.active == true)
            {
                handle_collision('t');
                block.setFillColor(sf::Color(0, 0, 0));
                hit_block();
            }
        }
    }
    else if(temp_x <= main_block.right_bside && temp_x > main_block.right_bside - 0.1)
    {
        if(temp_y >= main_block.top_bside && temp_y <= main_block.bottom_bside)
        {
            if (main_block.active == true)
            {
                handle_collision('l');
                block.setFillColor(sf::Color(0, 0, 0));
                hit_block();
            }
        }
    }
}



