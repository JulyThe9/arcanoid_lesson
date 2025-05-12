/**
*@file collision_handler.h
*@brief handles collisions for blocks, walls, platform, etc.

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


// ---------------------------------
// WALL COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief handles wall collision
*/
void handle_collision_walls()
{
    if(curr_gamestate.ball.curr_x >= right_wall - curr_gamestate.ball.size_radius * 2)
    {
#ifdef DEBUG
        cout << "-------------RIGHT WALL--------------" << endl;
        cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
#endif
        last_collision = COLLISION_CASE_RIGHT;
        handle_collision(COLLISION_CASE_RIGHT);

        /*
        sf::Sound current_sound(buffer_wall);
        current_sound.play();
        */
    }
    else if(curr_gamestate.ball.curr_y <= status_bar_length)
    {
#ifdef DEBUG
        cout << "-------------TOP WALL----------------" << endl;
        cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
#endif
        last_collision = COLLISION_CASE_TOP;
        handle_collision(COLLISION_CASE_TOP);

        /*
        sf::Sound current_sound(buffer_wall);
        current_sound.play();
        */
    }
    else if(curr_gamestate.ball.curr_x <= left_wall)
    {
#ifdef DEBUG
        cout << "-------------LEFT WALL---------------" << endl;
        cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
#endif
        last_collision = COLLISION_CASE_LEFT;
        handle_collision(COLLISION_CASE_LEFT);

        /*
        sf::Sound current_sound(buffer_wall);
        current_sound.play();
        */
    }
}

// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief handles platform collision
*/
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
            last_collision = COLLISION_CASE_BOTTOM;
            curr_degrees = get_new_angle();

            /*
            sf::Sound current_sound(buffer_platform);
            current_sound.play();
            */
        }
    }
}

//make block disappear
/**
*@brief makes block disappear

*sets all necessary values to 0, to make it invisible to the user and basically non-existant
*also checked for explosion block and if a chainreaction is occuring
*also checks if game is won or still continuing in case all blocks have been hit

*@param row current row of block that has been hit
*@param col current column of block that has been hit
*/
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

    sf::SoundBuffer current_buffer = map_sounds(curr_gamestate.blocks[row][col].block_sound);
    current_buffer.setBuffer(current_buffer);
    current_sound.play();


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
        set_game_won();
    }
}


/**
*@brief changes game status and deducts a life if true
*/
void hit_barrier()
{
    static int heart_number = curr_gamestate.lives_amount - 1;

    if(heart_number != 0)
    {
        if(!godmode_active)
        {
            last_collision = COLLISION_CASE_BOTTOM;
            set_loss_of_life(heart_number);
        }
    }
    else
    {
        if(!godmode_active)
        {
            last_collision = COLLISION_CASE_BOTTOM;
            set_game_loss(heart_number);
        }
    }
}


/**
*@brief checks if any block has been hit

*handles collisions for all active blocks

*@param i row of block
*@param j column of block
*/
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
           curr_gamestate.blocks[i][j].active &&
           last_collision != COLLISION_CASE_BOTTOM)
        {
#ifdef DEBUG
            cout << "-------COLLISION CASE BOTTOM---------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
            cout << "top block side: " << curr_gamestate.blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_gamestate.blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_gamestate.blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_gamestate.blocks[i][j].right_bside << endl;
#endif
            last_collision = COLLISION_CASE_BOTTOM;
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
           curr_gamestate.blocks[i][j].active &&
           last_collision != COLLISION_CASE_RIGHT)
        {
#ifdef DEBUG
            cout << "--------COLLISION CASE RIGHT---------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius << endl;
            cout << "top block side: " << curr_gamestate.blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_gamestate.blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_gamestate.blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_gamestate.blocks[i][j].right_bside << endl;
#endif
            last_collision = COLLISION_CASE_RIGHT;
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
           curr_gamestate.blocks[i][j].active &&
           last_collision != COLLISION_CASE_TOP)
        {
#ifdef DEBUG
            cout << "----------COLLISION CASE TOP---------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius << endl;
            cout << "top block side: " << curr_gamestate.blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_gamestate.blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_gamestate.blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_gamestate.blocks[i][j].right_bside << endl;
#endif
            last_collision = COLLISION_CASE_TOP;
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
           curr_gamestate.blocks[i][j].active &&
           last_collision != COLLISION_CASE_LEFT)
        {
#ifdef DEBUG
            cout << "--------COLLISION CASE LEFT----------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius << endl;
            cout << "top block side: " << curr_gamestate.blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_gamestate.blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_gamestate.blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_gamestate.blocks[i][j].right_bside << endl;
#endif
            last_collision = COLLISION_CASE_LEFT;
            curr_gamestate.ball.curr_x = curr_gamestate.blocks[i][j].right_bside;
            handle_collision(COLLISION_CASE_LEFT);
            hit_block(i, j);
        }
    }
}


// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief calls function to check all block side collisions
*/
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
/**
*@brief handles barrier collision
*/
void handle_collision_barrier()
{
    if(curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 > barrier_obj.y)
    {
#ifdef DEBUG
            cout << "---------COLLISION BARRIER-----------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius << endl;
            cout << "barrier y: " << barrier_obj.y << endl;
#endif
        last_collision = COLLISION_CASE_BOTTOM;
        hit_barrier();
        handle_collision(COLLISION_CASE_BOTTOM);

        /*
        sf::Sound current_sound(buffer_wall);
        current_sound.play();
        */
    }
}


/**
*@brief checks if state of game is off/false
*/
void check_gamestate()
{
    if(game_active == false)
    cout << "--Game Over--" << endl;
}
