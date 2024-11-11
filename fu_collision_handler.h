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
    vect1[0].active = false;
    block.setFillColor(sf::Color(0, 0, 0));
}

// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    if(temp_y + ball_size * 2 >= vect1[0].top_bside && temp_y < vect1[0].top_bside + 0.1)
    {
        if(temp_x > vect1[0].blockX && temp_x < vect1[0].blockX + vect1[0].block_width)
        {
            if (vect1[0].active == true)
            {
                handle_collision('b');
                hit_block();
            }
        }
    }
    else if(temp_x + ball_size * 2 >= vect1[0].left_bside && temp_x < vect1[0].left_bside + 0.1)
    {
        if(temp_y > vect1[0].top_bside && temp_y < vect1[0].bottom_bside)
        {
            if (vect1[0].active == true)
            {
                handle_collision('r');
                hit_block();
            }
        }
    }
    else if(temp_y <= vect1[0].bottom_bside && temp_y > vect1[0].bottom_bside - 0.1)
    {
        if(temp_x > vect1[0].left_bside + ball_size && temp_x < vect1[0].right_bside)
        {
            if (vect1[0].active == true)
            {
                handle_collision('t');
                hit_block();
            }
        }
    }
    else if(temp_x <= vect1[0].right_bside && temp_x > vect1[0].right_bside - 0.1)
    {
        if(temp_y >= vect1[0].top_bside && temp_y <= vect1[0].bottom_bside)
        {
            if (vect1[0].active == true)
            {
                handle_collision('l');
                hit_block();
            }
        }
    }
}
