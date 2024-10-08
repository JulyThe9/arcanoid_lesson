

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


// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    if(temp_y + ball_size * 2 >= top_bside && temp_y < top_bside + 0.1)
    {
        if(temp_x > blockX && temp_x < blockX + block_width)
        {
            handle_collision('b');
        }
    }
    else if(temp_x + ball_size * 2 >= left_bside && temp_x < left_bside + 0.1)
    {
        if(temp_y > top_bside && temp_y < bottom_bside)
        {
            handle_collision('r');
        }
    }
    else if(temp_y <= bottom_bside && temp_y > bottom_bside - 0.1)
    {
        if(temp_x > left_bside + ball_size && temp_x < right_bside)
        {
            handle_collision('t');
        }
    }
    else if(temp_x <= right_bside && temp_x > right_bside - 0.1)
    {
        if(temp_y >= top_bside && temp_y <= bottom_bside)
        {
            handle_collision('l');
        }
    }
}
