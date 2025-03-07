// ---------------------------------
// WALL COLLISION DETECTION HERE
// ---------------------------------

void handle_collision_walls()
{
    if(temp_y >= bottom_wall - ball_size * 2)
        {
            handle_collision(COLLISION_CASE_BOTTOM);
        }
        else if(temp_x >= right_wall - ball_size * 2)
        {
            handle_collision(COLLISION_CASE_RIGHT);
        }
        else if(temp_y <= top_wall)
        {
            handle_collision(COLLISION_CASE_TOP);
        }
        else if(temp_x <= left_wall)
        {
            handle_collision(COLLISION_CASE_LEFT);
        }
}


// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_platform()
{
    if(temp_y + ball_size * 2 >= platY && temp_y + ball_size * 2 < platY + collision_margin)
    {
        if(temp_x + ball_size > platX && temp_x < platX + curr_gamestate.plat_width)
        if(temp_x + ball_size > platX && temp_x < platX + curr_gamestate.plat_width)
        {
            curr_degrees = get_new_angle();
        }
    }
}

//make block disappear
void hit_block(int row, int col)
{
    int sum = 0;
    //add current hit block value to sum
    sum += curr_gamestate.blocks[row][col].block_value;
    vector<pair<int, int>> neighbours;
    //true = big explosion, false = small explosion

    if(curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
       curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
    {
        cout << "Block[" << row << ", " << col << "] has " << neighbours.size() << " neighbors" << endl;
        cout << "---" << endl;
        neighbours = get_neighbours(row, col);
    }
    cout << "Hit Block[" << row << ", " << col << "]" << endl;


    for(int i = 0; i < neighbours.size(); i++)
    {
        int curr_row = neighbours[i].first;
        int curr_col = neighbours[i].second;
        sum += curr_gamestate.blocks[curr_row][curr_col].block_value;

        cout << "Neighbor "<< i + 1
            << ": Location [" << neighbours[i].first << ", " << neighbours[i].second
            << "], Type: " << curr_gamestate.blocks[curr_row][curr_col].texturetype
            << ", Value: " << curr_gamestate.blocks[curr_row][curr_col].block_value << endl;

        //this line is used to set the active variable of neighbours of explosion block to false
        curr_gamestate.blocks[neighbours[i].first][neighbours[i].second].active = false;
        curr_gamestate.blocks_graphics[neighbours[i].first][neighbours[i].second].setFillColor(sf::Color(0, 0, 0));
        add_to_score(neighbours[i].first, neighbours[i].second);
    }

    for(int i = 0; i < neighbours.size(); i++)
    {
        if(curr_gamestate.blocks[neighbours[i].first][neighbours[i].second].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
           curr_gamestate.blocks[neighbours[i].first][neighbours[i].second].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
        {
            hit_block(neighbours[i].first, neighbours[i].second);
        }
    }
    cout << "Sum of all Values: " << sum << endl;
    neighbours.clear();
    //this line is used to set the active variable of explosion block to false
    curr_gamestate.blocks[row][col].active = false;
    curr_gamestate.blocks_graphics[row][col].setFillColor(sf::Color(0, 0, 0));
    add_to_score(row, col);
}

void handle_collision_all_sides(int i, int j)
{
    if(temp_y + ball_size * 2 >= curr_gamestate.blocks[i][j].top_bside &&
       temp_y + ball_size * 2 < curr_gamestate.blocks[i][j].top_bside + collision_margin)
    {
        if(temp_x + ball_size * 2 > curr_gamestate.blocks[i][j].blockX &&
           temp_x < curr_gamestate.blocks[i][j].right_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            handle_collision(COLLISION_CASE_BOTTOM);
            hit_block(i, j);
        }
    }
    else if(temp_x + ball_size * 2 >= curr_gamestate.blocks[i][j].left_bside &&
            temp_x + ball_size * 2 < curr_gamestate.blocks[i][j].left_bside + collision_margin)
    {
        if(temp_y + ball_size * 2 > curr_gamestate.blocks[i][j].top_bside &&
           temp_y < curr_gamestate.blocks[i][j].bottom_bside &&
           curr_gamestate.blocks[i][j].active)
        {

            handle_collision(COLLISION_CASE_RIGHT);
            hit_block(i, j);
        }
    }
    else if(temp_y <= curr_gamestate.blocks[i][j].bottom_bside &&
            temp_y > curr_gamestate.blocks[i][j].bottom_bside - collision_margin)
    {
        if(temp_x + ball_size * 2 > curr_gamestate.blocks[i][j].left_bside &&
           temp_x < curr_gamestate.blocks[i][j].right_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            handle_collision(COLLISION_CASE_TOP);
            hit_block(i, j);
        }
    }
    else if(temp_x <= curr_gamestate.blocks[i][j].right_bside &&
            temp_x > curr_gamestate.blocks[i][j].right_bside - collision_margin)
    {
        if(temp_y + ball_size * 2 >= curr_gamestate.blocks[i][j].top_bside &&
           temp_y <= curr_gamestate.blocks[i][j].bottom_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            handle_collision(COLLISION_CASE_LEFT);
            hit_block(i, j);
        }
    }
}

// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_block()
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            handle_collision_all_sides(i, j);
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
        handle_collision(COLLISION_CASE_BOTTOM);
        //block_disappear();
    }
}

