

void play_wall_sound()
{
    sound_wall.setBuffer(buffer_wall);
    sound_wall.setVolume(10);
    sound_wall.play();
}



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

        play_wall_sound();
    }
    else if(curr_gamestate.ball.curr_y <= status_bar_length)
    {
#ifdef DEBUG
        cout << "-------------TOP WALL----------------" << endl;
        cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
#endif
        last_collision = COLLISION_CASE_TOP;
        handle_collision(COLLISION_CASE_TOP);

        play_wall_sound();
    }
    else if(curr_gamestate.ball.curr_x <= left_wall)
    {
#ifdef DEBUG
        cout << "-------------LEFT WALL---------------" << endl;
        cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y << endl;
#endif
        last_collision = COLLISION_CASE_LEFT;
        handle_collision(COLLISION_CASE_LEFT);

        play_wall_sound();
    }
}


void does_timer_exist(bool &timer_exists, std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_spec_powerup)
{
    for (int i = 0; i < cooldown_bars.size(); ++i)
    {
        if (cooldown_bars[i].powerup_effect == curr_spec_powerup && cooldown_bars[i].timer_active)
        {
            cooldown_bars[i].powerup_clock.restart();
            timer_exists = true;
            break;
        }
    }
}


void create_new_timers(bool &timer_exists, std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_spec_powerup, int i)
{
    if (timer_exists == false)
    {
        int pos_x = SCREENSIZE_X - 110;
        int pos_y = SCREENSIZE_Y - 50 - (cooldown_bars.size() * (TIMER_HEIGHT + 10));

        timer_type new_timer(pos_x, pos_y, falling_powerups[i].type, curr_spec_powerup);
        new_timer.timer_active = true;
        cooldown_bars.push_back(new_timer);
    }
}


void clean_up_timers()
{
    for (int i = 0; i < falling_powerups.size(); i++)
    {
        falling_powerups[i].powerup_active = false;
    }
    for (int i = 0; i < cooldown_bars.size(); i++)
    {
        cooldown_bars[i].timer_active = false;
    }
    cooldown_bars.clear();
}

void create_powerup(int row, int col)
{
    int powerup_generation_chance = (std::rand() % 100);
    if (powerup_generation_chance >= 0)
    {
        int powerup_type_chance = (std::rand() % 100);
        falling_powerup_type curr_falling_powerup(0, 0, POWERUP_SPEED, curr_gamestate.blocks[row][col], BUFF);

        powerup_class_types curr_powerup_type = get_weighted_random(powerup_class_map);
        //cout << "type: " << curr_powerup_type << endl;

        if (curr_powerup_type == BUFF)
        {
            powerup_buff_effect_types buff = get_weighted_random(buff_map);
            //cout << "buff: " << buff << endl;
            //cout << "---------" << endl;
        }
        else if (curr_powerup_type == DEBUFF)
        {
            powerup_debuff_effect_types debuff = get_weighted_random(debuff_map);
            //cout << "debuff: " << debuff << endl;
            //cout << "---------" << endl;
        }
        else
        {
            powerup_joker_effect_types joker = get_weighted_random(joker_map);
            //cout << "joker: " << joker << endl;
            //cout << "---------" << endl;
        }

        int curr_powerup_x = curr_gamestate.blocks[row][col].blockX + ((BLOCK_WIDTH - POWERUP_WIDTH) / 2);
        int curr_powerup_y = curr_gamestate.blocks[row][col].blockY;

        curr_falling_powerup = falling_powerup_type(curr_powerup_x,
                                    curr_powerup_y,
                                    POWERUP_SPEED,
                                    curr_gamestate.blocks[row][col],
                                    curr_powerup_type);

        curr_falling_powerup.powerup_active = true;
        falling_powerups.push_back(curr_falling_powerup);
    }
}

void handle_collision_powerup()
{
    double collision_margin = curr_gamestate.ball.speed;

    for (int i = 0; i < falling_powerups.size(); i++)
    {
        sf::Vector2f position = falling_powerups[i].rectangle.getPosition();

        if (position.y > curr_gamestate.platform.y - curr_gamestate.platform.len - 20 &&
            position.y < curr_gamestate.platform.y - curr_gamestate.platform.len - 20 + collision_margin)
        {
            if (position.x + POWERUP_WIDTH > curr_gamestate.platform.x &&
                position.x < curr_gamestate.platform.x + curr_gamestate.platform.width + POWERUP_WIDTH)
            {
                std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_powerup_effect = falling_powerups[i].powerup_effect;

                bool timer_exists = false;

                does_timer_exist(timer_exists, curr_powerup_effect);
                create_new_timers(timer_exists, curr_powerup_effect, i);

                falling_powerups[i].powerup_active = false;
                falling_powerups.erase(falling_powerups.begin() + i);
                i--;
            }
        }
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
    double collision_margin = curr_gamestate.ball.speed;
    double collision_margin_godmode = godspeed;

    if (curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 >= curr_gamestate.platform.y &&
        (curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.platform.y + collision_margin ||
         curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius * 2 < curr_gamestate.platform.y + collision_margin_godmode))
    {
        if (curr_gamestate.ball.curr_x + curr_gamestate.ball.size_radius > curr_gamestate.platform.x &&
            curr_gamestate.ball.curr_x < curr_gamestate.platform.x + curr_gamestate.platform.width)
        {
            last_collision = COLLISION_CASE_BOTTOM;
            curr_degrees = get_new_angle();

            current_sound.setBuffer(buffer_platform);
            current_sound.play();
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
        create_powerup(curr_row, curr_col);
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

    current_buffer = map_sounds(curr_gamestate.blocks[row][col].block_sound);
    current_sound.setBuffer(current_buffer);
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

    create_powerup(row, col);
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


void handle_deletion_powerup()
{
    for(int i = 0; i < falling_powerups.size(); i++)
    {
        sf::Vector2f position = falling_powerups[i].rectangle.getPosition();
        if(position.y > barrier_obj.y - POWERUP_LEN)
        {
            falling_powerups[i].powerup_active = false;
            falling_powerups.erase(falling_powerups.begin() + i);
        }
    }
}
