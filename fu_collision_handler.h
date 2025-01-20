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
    if(temp_y + ball_size * 2 >= platY && temp_y + ball_size * 2 < platY + 0.07)
    {
        if(temp_x + ball_size * 2 > platX && temp_x < platX + plat_width)
        {
            curr_degrees = get_new_angle();
        }
    }
}

//hit block colour black
void hit_block(int i)
{
    vector_data_block[i].active = false;
    vector_graphics_block[i].setFillColor(sf::Color(0, 0, 0));
}



// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    for (int i = 0; i < block_amount; i++)
    {
        if(temp_y + ball_size * 2 >= vector_data_block[i].top_bside && temp_y + ball_size * 2 < vector_data_block[i].top_bside + 0.1)
        {
            if(temp_x + ball_size * 2 > vector_data_block[i].blockX && temp_x + ball_size * 2 < vector_data_block[i].blockX + vector_data_block[i].block_width)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('b');
                    hit_block(i);

                }
            }
        }
        else if(temp_x + ball_size * 2 >= vector_data_block[i].left_bside && temp_x + ball_size * 2 < vector_data_block[i].left_bside + 0.1)
        {
            if(temp_y + ball_size * 2 > vector_data_block[i].top_bside && temp_y + ball_size * 2 < vector_data_block[i].bottom_bside)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('r');
                    hit_block(i);
                }
            }
        }
        else if(temp_y <= vector_data_block[i].bottom_bside && temp_y > vector_data_block[i].bottom_bside - 0.1)
        {
            if(temp_x + ball_size * 2 > vector_data_block[i].left_bside && temp_x < vector_data_block[i].right_bside)
            {
                if (vector_data_block[i].active == true)
                {
                    handle_collision('t');
                    hit_block(i);
                }
            }
        }
        else if(temp_x <= vector_data_block[i].right_bside && temp_x > vector_data_block[i].right_bside - 0.1)
        {
            if(temp_y + ball_size * 2 >= vector_data_block[i].top_bside && temp_y <= vector_data_block[i].bottom_bside)
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

