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

void hit_block(int i)
{
    vector_data[i].active = false;
    vector_graphics[i].setFillColor(sf::Color(0, 0, 0));
    cout << "collided with block num: " << i << endl;
}

// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    for (int i = 0; i < block_amount; i++)
    {
        if(temp_y + ball_size * 2 >= vector_data[i].top_bside && temp_y < vector_data[i].top_bside + 0.1)
        {
            if(temp_x > vector_data[i].blockX && temp_x < vector_data[i].blockX + vector_data[i].block_width)
            {
                if (vector_data[i].active == true)
                {
                    handle_collision('b');
                    hit_block(i);
                }
            }
        }
        else if(temp_x + ball_size * 2 >= vector_data[i].left_bside && temp_x < vector_data[i].left_bside + 0.1)
        {
            if(temp_y > vector_data[i].top_bside && temp_y < vector_data[i].bottom_bside)
            {
                if (vector_data[i].active == true)
                {
                    handle_collision('r');
                    hit_block(i);
                }
            }
        }
        else if(temp_y <= vector_data[i].bottom_bside && temp_y > vector_data[i].bottom_bside - 0.1)
        {
            if(temp_x > vector_data[i].left_bside + ball_size && temp_x < vector_data[i].right_bside)
            {
                if (vector_data[i].active == true)
                {
                    handle_collision('t');
                    hit_block(i);
                }
            }
        }
        else if(temp_x <= vector_data[i].right_bside && temp_x > vector_data[i].right_bside - 0.1)
        {
            if(temp_y >= vector_data[i].top_bside && temp_y <= vector_data[i].bottom_bside)
            {
                if (vector_data[i].active == true)
                {
                    handle_collision('l');
                    hit_block(i);
                }
            }
        }
    }
}

