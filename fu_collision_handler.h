// ---------------------------------
// WALL COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_walls()
{
    if(curr_gamestate.ball.curr_y >= bottom_wall - curr_gamestate.ball.size_radius * 2)
    {
        handle_collision(COLLISION_CASE_BOTTOM);
    }
    else if(curr_gamestate.ball.curr_x >= right_wall - curr_gamestate.ball.size_radius * 2)
    {
        handle_collision(COLLISION_CASE_RIGHT);
    }
    else if(curr_gamestate.ball.curr_y <= status_bar_length)
    {
        handle_collision(COLLISION_CASE_TOP);
    }
    else if(curr_gamestate.ball.curr_x <= left_wall)
    {
        handle_collision(COLLISION_CASE_LEFT);
    }
}

// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
void handle_collision_platform()
{
    // margin for collisions for normal speed
    double collision_margin = curr_gamestate.ball.speed;
    // margin for collisions for godspeed
    double collision_margin_godmode = godspeed;

    if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 >= curr_gamestate.platform.y &&
       (curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.platform.y + collision_margin ||
        curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.platform.y + collision_margin_godmode))
    {
        if(curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius > curr_gamestate.platform.x &&
           curr_gamestate.ball.curr_x < curr_gamestate.platform.x + curr_gamestate.platform.width)
        if(curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius > curr_gamestate.platform.x &&
           curr_gamestate.ball.curr_x < curr_gamestate.platform.x + curr_gamestate.platform.width)
        {
            curr_degrees = get_new_angle();
        }
    }
}

//make block disappear
void hit_block(int row, int col)
{
    if(curr_gamestate.blocks[row][col].active)
        curr_gamestate.block_amount--;

    curr_gamestate.blocks[row][col].active = false;
    vector<pair<int, int>> neighbours;

    if(curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
       curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
    {
        neighbours = get_neighbours(row, col);
    }

    for(unsigned int i = 0; i < neighbours.size(); i++)
    {
        curr_gamestate.block_amount--;
        int curr_row = neighbours[i].first;
        int curr_col = neighbours[i].second;
        //this line is used to set the active variable of neighbours of explosion block to false
        curr_gamestate.blocks[curr_row][curr_col].active = false;
        curr_gamestate.blocks_graphics[curr_row][curr_col].setFillColor(sf::Color(0, 0, 0));
        add_to_score(curr_row, curr_col);
    }


    for(unsigned int i = 0; i < neighbours.size(); i++)
    {
        int curr_row = neighbours[i].first;
        int curr_col = neighbours[i].second;

        if(curr_gamestate.blocks[curr_row][curr_col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
           curr_gamestate.blocks[curr_row][curr_col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
        {
            hit_block(curr_row, curr_col);
        }
    }

    //this line is used to set the active variable of explosion block to false
    curr_gamestate.blocks_graphics[row][col].setFillColor(sf::Color(0, 0, 0));
    add_to_score(row, col);

    if(curr_gamestate.block_amount == 3)
    {
        if(godmode_active)
        {
            crazy_ballspeed = true;
            curr_gamestate.ball.speed = godspeed;
        }
    }

    if(curr_gamestate.block_amount == 0)
    {
        SetGameWon();
    }
}

void hit_barrier()
{
    static int heart_number = curr_gamestate.lives_amount - 1;

    if(heart_number != 0)
    {
        if(!godmode_active)
        {
            SetLossOfLife(heart_number);
        }
    }
    else
    {
        if(!godmode_active)
        {
            SetGameLoss(heart_number);
        }
    }
}

void handle_collision_all_sides(int i, int j)
{
    // margin for collisions for normal speed
    double collision_margin = curr_gamestate.ball.speed;
    // margin for collisions for godspeed
    double collision_margin_godmode = godspeed;

    //hit top side
    if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 > curr_gamestate.blocks[i][j].top_bside &&
       (curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.blocks[i][j].top_bside + collision_margin ||
       curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.blocks[i][j].top_bside + collision_margin_godmode))
    {
        if(curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius * 2 > curr_gamestate.blocks[i][j].blockX &&
           curr_gamestate.ball.curr_x < curr_gamestate.blocks[i][j].right_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            curr_gamestate.ball.curr_y = curr_gamestate.blocks[i][j].top_bside - (2 * curr_gamestate.ball.size_radius);
            handle_collision(COLLISION_CASE_BOTTOM);
            hit_block(i, j);
        }
    }
    //hit left side
    else if(curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius * 2 > curr_gamestate.blocks[i][j].left_bside &&
            (curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius * 2 < curr_gamestate.blocks[i][j].left_bside + collision_margin ||
            curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius * 2 < curr_gamestate.blocks[i][j].left_bside + collision_margin_godmode))
    {
        if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 > curr_gamestate.blocks[i][j].top_bside &&
           curr_gamestate.ball.curr_y < curr_gamestate.blocks[i][j].bottom_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            curr_gamestate.ball.curr_x = curr_gamestate.blocks[i][j].left_bside - (2 * curr_gamestate.ball.size_radius);
            handle_collision(COLLISION_CASE_RIGHT);
            hit_block(i, j);
        }
    }
    //hit bottom side
    else if(curr_gamestate.ball.curr_y < curr_gamestate.blocks[i][j].bottom_bside &&
            (curr_gamestate.ball.curr_y > curr_gamestate.blocks[i][j].bottom_bside - collision_margin ||
            curr_gamestate.ball.curr_y > curr_gamestate.blocks[i][j].bottom_bside - collision_margin_godmode))
    {
        if(curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius * 2 > curr_gamestate.blocks[i][j].left_bside &&
           curr_gamestate.ball.curr_x < curr_gamestate.blocks[i][j].right_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            curr_gamestate.ball.curr_y = curr_gamestate.blocks[i][j].bottom_bside;
            handle_collision(COLLISION_CASE_TOP);
            hit_block(i, j);
        }
    }
    //hit right side
    else if(curr_gamestate.ball.curr_x <= curr_gamestate.blocks[i][j].right_bside &&
            curr_gamestate.ball.curr_x > curr_gamestate.blocks[i][j].right_bside - collision_margin)
    {
        if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 >= curr_gamestate.blocks[i][j].top_bside &&
           curr_gamestate.ball.curr_y <= curr_gamestate.blocks[i][j].bottom_bside &&
           curr_gamestate.blocks[i][j].active)
        {
            curr_gamestate.ball.curr_x = curr_gamestate.blocks[i][j].right_bside;
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
    if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 > barrierY)
    {
        hit_barrier();
        handle_collision(COLLISION_CASE_BOTTOM);
    }
}

void check_gamestate()
{
    if(game_active == false)
    cout << "--Game Over--" << endl;
}
