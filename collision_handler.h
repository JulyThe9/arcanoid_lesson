/**
*@file collision_handler.h
*@brief handles collisions for blocks, walls, platform, etc.

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


void reset_platform(sf::RectangleShape &plat, sf::RenderWindow &main_window)
{
    curr_gamestate.platform.width = PLATFORM_WIDTH;
    curr_gamestate.platform.x = PLATFORM_INITIAL_X;
    curr_gamestate.platform.y = PLATFORM_INITIAL_Y;
    sf::Mouse::setPosition({curr_gamestate.platform.x, curr_gamestate.platform.y}, main_window);
    plat.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);
}


void reset_ball(sf::CircleShape &ball)
{
    curr_gamestate.ball.curr_x = BALL_START_POSX;
    curr_gamestate.ball.curr_y = BALL_START_POSY;
    curr_degrees = BALL_STARTER_DEG;
    ball.setPosition(curr_gamestate.ball.curr_x, curr_gamestate.ball.curr_y);
}


//--------------------------------------------------------------------------------------------------
/**
*@brief makes block disappear

*sets all necessary values to 0, to make it invisible to the user and basically non-existant
*also checked for explosion block and if a chainreaction is occuring
*also checks if game is won or still continuing in case all blocks have been hit

*@param row current row of block that has been hit
*@param col current column of block that has been hit
*/
void hit_block(int row, int col, vector<vector<block_type>> &curr_blocks, vector<vector<sf::RectangleShape>> &curr_blocks_graphics, ball_type &curr_ball)
{
    if(!curr_ball.fake)
    {
        if(curr_blocks[row][col].active)
            curr_gamestate.block_amount--;
    }

    curr_blocks[row][col].active = false;
    vector<pair<int, int>> neighbours;

    if(curr_blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
       curr_blocks[row][col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
    {
        neighbours = get_neighbours(row, col, curr_blocks);
    }

    for(unsigned int i = 0; i < neighbours.size(); i++)
    {
        int curr_row = neighbours[i].first;
        int curr_col = neighbours[i].second;

        if (curr_blocks[curr_row][curr_col].active)
        {
            if(!curr_ball.fake)
                curr_gamestate.block_amount--;

            curr_blocks[curr_row][curr_col].active = false;
            curr_blocks_graphics[curr_row][curr_col].setFillColor(sf::Color(0, 0, 0));

            if(!curr_ball.fake)
            {
                add_to_score(curr_row, curr_col);
                create_powerup(curr_row, curr_col);
            }

            if (curr_blocks[curr_row][curr_col].texturetype == TEXTURE_TYPE_EXPLOSION_SMALL ||
                curr_blocks[curr_row][curr_col].texturetype == TEXTURE_TYPE_EXPLOSION_LARGE)
            {
                hit_block(curr_row, curr_col, curr_blocks, curr_blocks_graphics, curr_ball);
            }
        }
    }

    curr_blocks_graphics[row][col].setFillColor(sf::Color(0, 0, 0));

    if(!curr_ball.fake)
    {
        add_to_score(row, col);
        current_buffer = map_sounds(curr_gamestate.blocks[row][col].block_sound);
        current_sound.setBuffer(current_buffer);
        current_sound.play();
        create_powerup(row, col);
    }

    if(!curr_ball.fake && curr_gamestate.block_amount == 0)
        set_game_won();
}



sf::Vector2i lastMousePosition;
sf::Clock mouseSpeedClock;

// CHATGPT TO GET MOUSE SPEED
double get_mouse_vertical_speed()
{
    static sf::Vector2i lastMousePosition = sf::Mouse::getPosition();
    static sf::Clock clock;

    sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
    double deltaTime = clock.restart().asSeconds();

    if (deltaTime <= 0.0001)
        deltaTime = 0.0001; // avoid division by zero

    int dy = currentMousePosition.y - lastMousePosition.y;
    lastMousePosition = currentMousePosition;

    // No movement -> speed 0
    if (dy == 0)
        return 0.0;

    // Pixels per second
    double verticalSpeed = std::abs(static_cast<double>(dy)) / deltaTime;

    // Adjust divisor to taste: larger divisor = smaller numbers
    double scaledSpeed = verticalSpeed / 50.0;

    return scaledSpeed;
}


void handle_collision_powerup()
{
    double curr_mousespeed = get_mouse_vertical_speed();

    double collision_margin;

    if (!is_plat_y_axis_joker_active)
        collision_margin = curr_gamestate.ball.speed;
    else
    {
        collision_margin = (curr_mousespeed / 10) + curr_gamestate.ball.speed;
        //cout << "col marg: " << curr_mousespeed + curr_gamestate.ball.speed << endl;
    }


    for (int i = 0; i < falling_powerups.size(); i++)
    {
        sf::Vector2f position = falling_powerups[i].rectangle.getPosition();

        if (position.y > curr_gamestate.platform.y - curr_gamestate.platform.len - 20 &&
            position.y < curr_gamestate.platform.y - curr_gamestate.platform.len + collision_margin)
        {
            if (position.x + POWERUP_WIDTH > curr_gamestate.platform.x &&
                position.x < curr_gamestate.platform.x + curr_gamestate.platform.width + POWERUP_WIDTH)
            {
                std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_powerup_effect = falling_powerups[i].powerup_effect;

                bool timer_exists = false;

                // checks if a timer already exists
                does_timer_exist(timer_exists, curr_powerup_effect);
                if(!timer_exists)
                    create_new_timers(curr_powerup_effect, i);

                powerup_activity();
                falling_powerups[i].powerup_active = false;
                falling_powerups.erase(falling_powerups.begin() + i);
                i--;
            }
        }
    }
}


void move_ball_back(ball_type &ball, double overlap_distance)
{
    double direction_length = sqrt(ball.alpha_x * ball.alpha_x + ball.alpha_y * ball.alpha_y);

    if(direction_length != 0)
    {
        double direction_x = ball.alpha_x / direction_length;
        double direction_y = ball.alpha_y / direction_length;

        ball.curr_x -= direction_x * overlap_distance;
        ball.curr_y -= direction_y * overlap_distance;
    }
}


// ---------------------------------
// WALL COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief handles wall collision
*/
void handle_collision_walls(ball_type &curr_ball)
{
    if(curr_ball.curr_x >= right_wall - curr_ball.size_radius * 2)
    {
#ifdef DEBUG
        cout << "-------------RIGHT WALL--------------" << endl;
        cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y << endl;
#endif
        double overlap_distance = curr_ball.curr_x - (right_wall - curr_ball.size_radius * 2);
        move_ball_back(curr_ball, overlap_distance);

        curr_ball.last_collision = COLLISION_CASE_RIGHT;
        handle_collision(COLLISION_CASE_RIGHT, curr_ball);

        if(!curr_ball.fake)
            play_wall_sound();
    }
    else if(curr_ball.curr_y <= status_bar_length)
    {
#ifdef DEBUG
        cout << "-------------TOP WALL----------------" << endl;
        cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y << endl;
#endif
        double overlap_distance = status_bar_length - curr_ball.curr_y;
        move_ball_back(curr_ball, overlap_distance);

        curr_ball.last_collision = COLLISION_CASE_TOP;
        handle_collision(COLLISION_CASE_TOP, curr_ball);

        if(!curr_ball.fake)
            play_wall_sound();
        static int counter = 0;
        if(counter < 500)
        {
            cout << "handled collision wall 2" << endl;
            counter++;
        }
    }
    else if(curr_ball.curr_x <= left_wall)
    {
#ifdef DEBUG
        cout << "-------------LEFT WALL---------------" << endl;
        cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y << endl;
#endif
        double overlap_distance = left_wall - curr_ball.curr_x;
        move_ball_back(curr_ball, overlap_distance);

        curr_ball.last_collision = COLLISION_CASE_LEFT;
        handle_collision(COLLISION_CASE_LEFT, curr_ball);

        if(!curr_ball.fake)
            play_wall_sound();
        cout << "handled collision wall 3" << endl;
    }
}


/**
*@brief checks if any block has been hit

*handles collisions for all active blocks

*@param i row of block
*@param j column of block
*/
void handle_collision_all_sides(int i, int j, ball_type &curr_ball,
                                vector<vector<block_type>> &curr_blocks, vector<vector<sf::RectangleShape>> &curr_blocks_graphics)
{
    // margin for collisions for normal speed
    double collision_margin = curr_ball.speed;

    //hit top side
    if(curr_ball.curr_y + curr_ball.size_radius * 2 > curr_blocks[i][j].top_bside &&
       (curr_ball.curr_y + curr_ball.size_radius * 2 < curr_blocks[i][j].top_bside + collision_margin))
    {
        if(curr_ball.curr_x + curr_ball.size_radius * 2 > curr_blocks[i][j].blockX &&
           curr_ball.curr_x < curr_blocks[i][j].right_bside &&
           curr_blocks[i][j].active &&
           curr_ball.last_collision != COLLISION_CASE_BOTTOM)
        {
#ifdef DEBUG
            cout << "-------COLLISION CASE BOTTOM---------" << endl;
            cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y << endl;
            cout << "top block side: " << curr_blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_blocks[i][j].right_bside << endl;
#endif
            double overlap_distance = (curr_ball.curr_y + curr_ball.size_radius * 2) - curr_blocks[i][j].top_bside;
            move_ball_back(curr_ball, overlap_distance);

            curr_ball.last_collision = COLLISION_CASE_BOTTOM;
            handle_collision(COLLISION_CASE_BOTTOM, curr_ball);
            hit_block(i, j, curr_blocks, curr_blocks_graphics, curr_ball);
            cout << "handled collision block top side" << endl;
        }
    }
    //hit left side
    else if(curr_ball.curr_x + curr_ball.size_radius * 2 > curr_blocks[i][j].left_bside &&
            (curr_ball.curr_x + curr_ball.size_radius * 2 < curr_blocks[i][j].left_bside + collision_margin))
    {
        if(curr_ball.curr_y + curr_ball.size_radius * 2 > curr_blocks[i][j].top_bside &&
           curr_ball.curr_y < curr_blocks[i][j].bottom_bside &&
           curr_blocks[i][j].active &&
           curr_ball.last_collision != COLLISION_CASE_RIGHT)
        {
#ifdef DEBUG
            cout << "--------COLLISION CASE RIGHT---------" << endl;
            cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y + curr_ball.size_radius << endl;
            cout << "top block side: " << curr_blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_blocks[i][j].right_bside << endl;
#endif
            double overlap_distance = (curr_ball.curr_x + curr_ball.size_radius * 2) - curr_blocks[i][j].left_bside;
            move_ball_back(curr_ball, overlap_distance);

            curr_ball.last_collision = COLLISION_CASE_RIGHT;
            handle_collision(COLLISION_CASE_RIGHT, curr_ball);
            hit_block(i, j, curr_blocks, curr_blocks_graphics, curr_ball);
            cout << "handled collision block left side" << endl;
        }
    }
    //hit bottom side
    else if(curr_ball.curr_y < curr_blocks[i][j].bottom_bside &&
            (curr_ball.curr_y > curr_blocks[i][j].bottom_bside - collision_margin))
    {
        if(curr_ball.curr_x + curr_ball.size_radius * 2 > curr_blocks[i][j].left_bside &&
           curr_ball.curr_x < curr_blocks[i][j].right_bside &&
           curr_blocks[i][j].active &&
           curr_ball.last_collision != COLLISION_CASE_TOP)
        {
#ifdef DEBUG
            cout << "----------COLLISION CASE TOP---------" << endl;
            cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y + curr_ball.size_radius << endl;
            cout << "top block side: " << curr_blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_blocks[i][j].right_bside << endl;
#endif
            double overlap_distance = curr_blocks[i][j].bottom_bside - curr_ball.curr_y;
            move_ball_back(curr_ball, overlap_distance);

            curr_ball.last_collision = COLLISION_CASE_TOP;
            handle_collision(COLLISION_CASE_TOP, curr_ball);
            hit_block(i, j, curr_blocks, curr_blocks_graphics, curr_ball);
            cout << "handled collision block bottom side" << endl;

        }
    }
    //hit right side
    else if(curr_ball.curr_x <= curr_blocks[i][j].right_bside &&
            curr_ball.curr_x > curr_blocks[i][j].right_bside - collision_margin)
    {
        if(curr_ball.curr_y + curr_ball.size_radius * 2 >= curr_blocks[i][j].top_bside &&
           curr_ball.curr_y <= curr_blocks[i][j].bottom_bside &&
           curr_blocks[i][j].active &&
           curr_ball.last_collision != COLLISION_CASE_LEFT)
        {
#ifdef DEBUG
            cout << "--------COLLISION CASE LEFT----------" << endl;
            cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y + curr_ball.size_radius << endl;
            cout << "top block side: " << curr_blocks[i][j].top_bside << endl;
            cout << "left block side: " << curr_blocks[i][j].left_bside << endl;
            cout << "bottom block side: " << curr_blocks[i][j].bottom_bside << endl;
            cout << "right block side: " << curr_blocks[i][j].right_bside << endl;
#endif
            double overlap_distance = curr_blocks[i][j].right_bside - curr_ball.curr_x;
            move_ball_back(curr_ball, overlap_distance);

            curr_ball.last_collision = COLLISION_CASE_LEFT;
            curr_ball.curr_x = curr_blocks[i][j].right_bside;
            handle_collision(COLLISION_CASE_LEFT, curr_ball);
            hit_block(i, j, curr_blocks, curr_blocks_graphics, curr_ball);
            cout << "handled collision block right side" << endl;
        }
    }
}


// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief calls function to check all block side collisions
*/
void handle_collision_block(ball_type &curr_ball,
                            vector<vector<block_type>> &curr_blocks, vector<vector<sf::RectangleShape>> &curr_blocks_graphics)
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            handle_collision_all_sides(i, j, curr_ball, curr_blocks, curr_blocks_graphics);
        }
    }
}


void predict_trajectory(sf::RenderWindow &main_window, ball_type &curr_ball,
                        vector<vector<block_type>> &curr_blocks, vector<vector<sf::RectangleShape>> &curr_blocks_graphics, float curr_degrees)
{
    sf::VertexArray dots(sf::Points);

    curr_gamestate.dupe_ball.curr_x = curr_ball.curr_x;
    curr_gamestate.dupe_ball.curr_y = curr_ball.curr_y - curr_ball.speed;

    curr_gamestate.dupe_ball.recent_x = curr_ball.recent_x;
    curr_gamestate.dupe_ball.recent_y = curr_ball.recent_y;

    curr_gamestate.dupe_ball.speed = 3;

    curr_gamestate.dupe_ball.alpha_x = curr_ball.alpha_x;
    curr_gamestate.dupe_ball.alpha_y = curr_ball.alpha_y;



    curr_gamestate.dupe_ball.alpha_y = get_new_y(curr_degrees, curr_gamestate.dupe_ball) * (-1);

    cout << "half point of plat: " << SCREENSIZE_X - (curr_gamestate.platform.x + (curr_gamestate.platform.width / 2)) << endl;
    cout << "dupe ball x: " << curr_gamestate.dupe_ball.curr_x << endl;
    cout << "screensize: " << SCREENSIZE_X << endl;
    cout << "platform x pos: " << curr_gamestate.platform.x << endl;
    cout << "width / 2: " << curr_gamestate.platform.width / 2 << endl;

    int var = SCREENSIZE_X - (SCREENSIZE_X - (curr_gamestate.platform.x + (curr_gamestate.platform.width / 2)));
    if(var < curr_gamestate.dupe_ball.curr_x)
    {
        cout << "right" << endl;
        curr_gamestate.dupe_ball.alpha_x = get_new_x(curr_degrees, curr_gamestate.dupe_ball);
    }
    else
    {
        cout << "left" << endl;
        curr_gamestate.dupe_ball.alpha_x = get_new_x(curr_degrees, curr_gamestate.dupe_ball) * (-1);
    }



    curr_gamestate.dupe_ball.last_collision = COLLISION_CASE_BOTTOM;
    cout << "size of dupe blocks: " << curr_gamestate.dupe_blocks.size() << endl;
    cout << "size of curr_blocks: " << curr_blocks.size() << endl;

    curr_gamestate.dupe_blocks = curr_blocks;

    curr_gamestate.dupe_blocks_graphics = curr_blocks_graphics;

    float ball_start_prediction_y = curr_ball.curr_y;
    bool is_prediction_margin_valid;

    if(ball_start_prediction_y > PLATFORM_INITIAL_Y - curr_ball.size_radius * 2)
        is_prediction_margin_valid = true;

    while(curr_gamestate.dupe_ball.curr_y < PLATFORM_INITIAL_Y - curr_ball.size_radius * 2 || is_prediction_margin_valid)
    {
        if(curr_ball.curr_y < PLATFORM_INITIAL_Y - curr_ball.size_radius * 2)
            is_prediction_margin_valid = false;

        plat_movement(main_window);

        plat.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);

        curr_gamestate.ball.curr_x += curr_gamestate.ball.alpha_x;
        curr_gamestate.ball.curr_y += curr_gamestate.ball.alpha_y;

        curr_gamestate.dupe_ball.curr_x += curr_gamestate.dupe_ball.alpha_x;
        curr_gamestate.dupe_ball.curr_y += curr_gamestate.dupe_ball.alpha_y;

        dots.append(sf::Vertex(sf::Vector2f(curr_gamestate.dupe_ball.curr_x, curr_gamestate.dupe_ball.curr_y), sf::Color::Yellow));
        dots.append(sf::Vertex(sf::Vector2f(curr_gamestate.dupe_ball.curr_x + 1, curr_gamestate.dupe_ball.curr_y + 1), sf::Color::Yellow));
        dots.append(sf::Vertex(sf::Vector2f(curr_gamestate.dupe_ball.curr_x - 1, curr_gamestate.dupe_ball.curr_y - 1), sf::Color::Yellow));

        ball.setPosition(curr_gamestate.ball.curr_x, curr_gamestate.ball.curr_y);
        //dupe_ball.setPosition(curr_gamestate.dupe_ball.curr_x, curr_gamestate.dupe_ball.curr_y);

        handle_collision_walls(curr_gamestate.dupe_ball);
        handle_collision_block(curr_gamestate.dupe_ball, curr_gamestate.dupe_blocks, curr_gamestate.dupe_blocks_graphics);
        handle_collision_walls(curr_gamestate.ball);
        handle_collision_block(curr_gamestate.ball, curr_gamestate.blocks, curr_gamestate.blocks_graphics);
        handle_collision_powerup();

        draw_everything(main_window);
        main_window.draw(dots);
#ifdef TP_DEBUG
            draw_ball(main_window, dupe_ball);
#endif
        main_window.display();

        // Clear screen
        main_window.clear();
    }
    predicting_x = curr_gamestate.dupe_ball.curr_x - (curr_gamestate.platform.width / 2);
    predicting_y = curr_gamestate.dupe_ball.curr_y + curr_ball.size_radius * 2;
    is_trajectory_prediction_shown = true;
    curr_gamestate.ball.speed = BALL_SPEED;
    in_blinking_animation = true;
    cout << "speed of ball: " << curr_gamestate.ball.speed << endl;
    cout << "predicting x: " << curr_gamestate.dupe_ball.curr_x << endl;
    cout << "predicting y: " << curr_gamestate.dupe_ball.curr_y << endl;
    cout << "HURRAYYYY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}


// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
/**
*@brief handles platform collision
*/
void handle_collision_platform(sf::RenderWindow &main_window, ball_type &curr_ball,
                               vector<vector<block_type>> &curr_blocks, vector<vector<sf::RectangleShape>> &curr_blocks_graphics)
{
    double curr_mousespeed = get_mouse_vertical_speed();

    double collision_margin;

    if (!is_plat_y_axis_joker_active)
    {
        collision_margin = curr_ball.speed;
    }
    else
        collision_margin = curr_mousespeed + curr_ball.speed;

    if (curr_ball.curr_y + curr_ball.size_radius * 2 >= curr_gamestate.platform.y &&
        (curr_ball.curr_y + curr_ball.size_radius * 2 < curr_gamestate.platform.y + collision_margin))
    {
        if (curr_ball.curr_x + curr_ball.size_radius > curr_gamestate.platform.x &&
            curr_ball.curr_x < curr_gamestate.platform.x + curr_gamestate.platform.width &&
            curr_ball.last_collision != COLLISION_CASE_BOTTOM)
        {
            curr_ball.last_collision = COLLISION_CASE_BOTTOM;
            curr_degrees = get_new_angle(curr_ball);
            //last point of updating everything

            if(!curr_ball.fake)
            {
                current_sound.setBuffer(buffer_platform);
                current_sound.play();
            }

            if(is_trajectory_prediction_buff_active)
            {
                cout << "curr degrees: " << curr_degrees << endl;
                predict_trajectory(main_window, curr_ball, curr_gamestate.blocks, curr_blocks_graphics, curr_degrees);
            }
        }
    }
}





//--------------------------------------------------------------------------------------------------
/**
*@brief changes game status and deducts a life if true
*/
void hit_barrier()
{
    static int heart_number = curr_gamestate.lives_amount - 1;

    if(heart_number != 0)
    {
        set_loss_of_life(heart_number);
    }
    else
    {
        set_game_loss(heart_number);
    }
}


/**
*@brief handles barrier collision
*/
void handle_collision_barrier(ball_type &curr_ball, vector<vector<block_type>> &curr_blocks)
{
    if(curr_ball.curr_y + curr_ball.size_radius * 2 > barrier_obj.y)
    {
#ifdef DEBUG
            cout << "---------COLLISION BARRIER-----------" << endl;
            cout << "current ball pos: " << curr_ball.curr_x << " | " << curr_ball.curr_y + curr_ball.size_radius << endl;
            cout << "barrier y: " << barrier_obj.y << endl;
#endif
        curr_ball.last_collision = COLLISION_CASE_BOTTOM;
        hit_barrier();
        handle_collision(COLLISION_CASE_BOTTOM, curr_ball);
    }
}


//--------------------------------------------------------------------------------------------------
/**
*@brief checks if state of game is off/false
*/
void check_gamestate()
{
    if(game_active == false)
    cout << "--Game Over--" << endl;
}
