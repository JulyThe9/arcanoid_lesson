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
    if(temp_y + ball_size * 2 >= platY && temp_y + ball_size * 2 < platY + collision_margin)
    {
        if(temp_x + ball_size > platX && temp_x < platX + plat_width)
        if(temp_x + ball_size > platX && temp_x < platX + plat_width)
        {
            curr_degrees = get_new_angle();
        }
    }
}

//make block disappear
void hit_block(int block_number)
{
    vector_data_block[block_number].active = false;
    vector_graphics_block[block_number].setFillColor(sf::Color(0, 0, 0));

    add_to_score(block_number);
}



// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    for (int i = 0; i < block_amount; i++)
    {
        if(temp_y + ball_size * 2 >= vector_data_block[i].top_bside &&
           temp_y + ball_size * 2 < vector_data_block[i].top_bside + collision_margin)
        {
            if(temp_x + ball_size * 2 > vector_data_block[i].blockX &&
               temp_x + ball_size * 2 < vector_data_block[i].blockX + vector_data_block[i].block_width)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('b');
                    hit_block(i);
                }
            }
        }
        else if(temp_x + ball_size * 2 >= vector_data_block[i].left_bside &&
                temp_x + ball_size * 2 < vector_data_block[i].left_bside + collision_margin)
        {
            if(temp_y + ball_size * 2 > vector_data_block[i].top_bside &&
               temp_y < vector_data_block[i].bottom_bside)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('r');
                    hit_block(i);
                }
            }
        }
        else if(temp_y <= vector_data_block[i].bottom_bside &&
                temp_y > vector_data_block[i].bottom_bside - collision_margin)
        {
            if(temp_x + ball_size * 2 > vector_data_block[i].left_bside &&
               temp_x < vector_data_block[i].right_bside)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('t');
                    hit_block(i);
                }
            }
        }
        else if(temp_x <= vector_data_block[i].right_bside &&
                temp_x > vector_data_block[i].right_bside - collision_margin)
        {
            if(temp_y + ball_size * 2 >= vector_data_block[i].top_bside &&
               temp_y <= vector_data_block[i].bottom_bside)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('l');
                    hit_block(i);
                }
            }
        }
    }
}

//--------------------------
//COLLISIONDETECTION BARRIER
//--------------------------
void handle_collision_barrier()
{
    if(temp_y + ball_size * 2 > barrierY)
    {
        handle_collision('b');
        //block_disappear();
    }
}

