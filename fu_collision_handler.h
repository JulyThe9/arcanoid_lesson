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
        else if(temp_y <= status_bar_length)
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
    if(temp_y + ball_size * 2 >= platY &&
       (temp_y + ball_size * 2 < platY + collision_margin ||
        temp_y + ball_size * 2 < platY + collision_margin_godmode))
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
    if(curr_gamestate.blocks[row][col].active)
        curr_gamestate.block_amount--;

    curr_gamestate.blocks[row][col].active = false;
    vector<pair<int, int>> neighbours;

    if(curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
       curr_gamestate.blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
    {
        neighbours = get_neighbours(row, col);
    }

    for(int i = 0; i < neighbours.size(); i++)
    {
        curr_gamestate.block_amount--;
        int curr_row = neighbours[i].first;
        int curr_col = neighbours[i].second;
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

    //this line is used to set the active variable of explosion block to false
    curr_gamestate.blocks_graphics[row][col].setFillColor(sf::Color(0, 0, 0));
    add_to_score(row, col);

    if(curr_gamestate.block_amount == 3)
    {
        if(godmode_active)
        {
            crazy_ballspeed = true;
            curr_gamestate.ball_speed = godspeed;
        }
    }

    if(curr_gamestate.block_amount == 0)
    {
        game_won_text.setFont(font);
        game_won_text.setCharacterSize(50);
        game_won_text.setFillColor(sf::Color::Green);
        game_won_text.setStyle(sf::Text::Bold);
        game_won_text.setPosition(280, 700);
        game_won_text.setString("CONGRADULATIONS! YOU WON!");
        game_status = BLOCKS_GONE;
    }
}

void hit_barrier()
{
    static int heart_number = lives_amount - 1;
    if(heart_number != 0)
    {
        if(!godmode_active)
        {
            vector_life_data[heart_number].heart_texture = heart_texture_empty;
            heart_number--;
            heart_deduction_text.setFont(font);
            heart_deduction_text.setCharacterSize(50);
            heart_deduction_text.setFillColor(sf::Color::Yellow);
            heart_deduction_text.setStyle(sf::Text::Bold);
            heart_deduction_text.setPosition(280, 700);
            heart_deduction_text.setString("Press Space to continue..");
            game_status = HEART_DEDUCTION;
        }
    }
    else
    {
        if(!godmode_active)
        {
            vector_life_data[heart_number].heart_texture = heart_texture_empty;
            no_hearts_text.setFont(font);
            no_hearts_text.setCharacterSize(70);
            no_hearts_text.setFillColor(sf::Color::Red);
            no_hearts_text.setStyle(sf::Text::Bold);
            no_hearts_text.setPosition(screensizeX / 2 - 200, 700);
            no_hearts_text.setString("Game Over!");
            game_status = HEARTS_GONE;
        }
    }
}

void handle_collision_all_sides(int i, int j)
{
    if(temp_y + ball_size * 2 >= curr_gamestate.blocks[i][j].top_bside &&
       (temp_y + ball_size * 2 < curr_gamestate.blocks[i][j].top_bside + collision_margin ||
       temp_y + ball_size * 2 < curr_gamestate.blocks[i][j].top_bside + collision_margin_godmode))
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
            (temp_x + ball_size * 2 < curr_gamestate.blocks[i][j].left_bside + collision_margin ||
            temp_x + ball_size * 2 < curr_gamestate.blocks[i][j].left_bside + collision_margin_godmode))
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
            (temp_y > curr_gamestate.blocks[i][j].bottom_bside - collision_margin ||
            temp_y > curr_gamestate.blocks[i][j].bottom_bside - collision_margin_godmode))
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
        hit_barrier();
        handle_collision(COLLISION_CASE_BOTTOM);
    }
}

void check_gamestate()
{
    if(game_active == false)
    cout << "--Game Over--" << endl;
}

