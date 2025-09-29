/**
*@file init_misc.h
*@brief all drawing done for UI

*@author [Johannes Waldeck]
*@date [02.05.2025]
*/


/**
*@brief draws Platform

*@param main_window current game/sfml window
*@param plat object being drawn
*/
void draw_plat(sf::RenderWindow &main_window, sf::RectangleShape plat)
{
    main_window.draw(plat);
}

/**
*@brief draws Barrier

*@param main_window current game/sfml window
*@param barrier object being drawn
*/
void draw_barrier(sf::RenderWindow &main_window, sf::RectangleShape barrier)
{
    main_window.draw(barrier);
}

/**
*@brief draws Ball
*@param main_window current game/sfml window
*@param ball object being drawn
*/
void draw_ball(sf::RenderWindow &main_window, sf::CircleShape ball)
{
    main_window.draw(ball);
}

/**
*@brief draws statusbar(the gray background of entire statusbar)

*@param main_window current game/sfml window
*@param status_bar being drawn
*/
void draw_status_bar(sf::RenderWindow &main_window, sf::RectangleShape status_bar)
{
    main_window.draw(status_bar);
}

/**
*@brief draws logo on statusbar

*@param main_window current game/sfml window
*@param status_bar_logo object being drawn
*/
void draw_status_bar_logo(sf::RenderWindow &main_window, sf::RectangleShape status_bar_logo)
{
    main_window.draw(status_bar_logo);
}

/**
*@brief draws score

*@param main_window current game/sfml window
*/
void draw_score(sf::RenderWindow &main_window)
{
    main_window.draw(score);
}

/**
*@brief draws blocks

*draws blocks by i(rows) and j(cols)

*@param main_window current game/sfml window
*/
void draw_blocks(sf::RenderWindow &main_window)
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            main_window.draw(curr_gamestate.blocks_graphics[i][j]);
        }
    }
}

/**
*@brief draws Hearts

*draws hearts by lives_amount(amount of lives)

*@param main_window current game/sfml window
*/
void draw_hearts(sf::RenderWindow &main_window)
{
    for(int i = 0; i < curr_gamestate.lives_amount; i++)
    {
        main_window.draw(vector_graphics_life[i]);
    }
}

/**
*@brief draws Text of Game Won

*@param main_window current game/sfml window
*/
void draw_game_won_text(sf::RenderWindow &main_window)
{
    main_window.draw(game_won_text);
}

/**
*@brief draws Text of no Hearts

*@param main_window current game/sfml window
*/
void draw_no_hearts_text(sf::RenderWindow &main_window)
{
    main_window.draw(no_hearts_text);
}

/**
*@brief draws Text of Life deduction

*@param main_window current game/sfml window
*/

void draw_heart_deduction_text(sf::RenderWindow &main_window)
{
    main_window.draw(heart_deduction_text);
}


//----------------------------------------------------------------------------------------------------
void draw_powerup(sf::RenderWindow &main_window)
{
    for(int i = 0; i < falling_powerups.size(); i++)
    {
        if(falling_powerups[i].powerup_active)
        {
            float time;

            // if its the first frame that powerup is active
            if(falling_powerups[i].first_activation)
            {
                // restart clock
                falling_powerups[i].powerup_clock.restart();
                // set passed time to zero so it doesn't move instantly
                time = 0;
                falling_powerups[i].first_activation = false;
            }
            else
            {
                // restart the clock and get how much time passed since the last frame
                time = falling_powerups[i].powerup_clock.restart().asSeconds();
            }

            // get position
            sf::Vector2f position = falling_powerups[i].rectangle.getPosition();

            // move y axis accordingly downward
            position.y += falling_powerups[i].powerupSpeed * time;
            // set new position
            falling_powerups[i].rectangle.setPosition(position);

            main_window.draw(falling_powerups[i].rectangle);
        }
        else
        {
            // if powerup is not active, reset first activation for a propper setup for next time
            falling_powerups[i].first_activation = true;
        }
    }
}


//----------------------------------------------------------------------------------------------------
void check_specific_effect_timer_buff(powerup_buff_effect_types buff_type)
{
    //check for specific buffs
    if (buff_type == TRAJECTORY_PREDICTION)
    {
        cout << "timer ran out :(" << endl;
        trajectory_prediction_buff = false;
    }
}


void check_specific_effect_timer_debuff(powerup_debuff_effect_types debuff_type)
{
    //check for specific debuffs
}


void check_specific_effect_timer_joker(powerup_joker_effect_types joker_type)
{
    //check for specific jokers
    if (joker_type == PLAT_Y_AXIS)
    {
        cout << "timer ran out :(" << endl;
        curr_gamestate.platform.y = PLATFORM_INITIAL_Y;
        plat_y_axis_joker = false;
    }
}


//---------------------------------
void check_individual_effect_timer_buff(int i)
{
    powerup_buff_effect_types buff_type = std::get<powerup_buff_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_buff(buff_type);
}


void check_individual_effect_timer_debuff(int i)
{
    powerup_debuff_effect_types debuff_type = std::get<powerup_debuff_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_debuff(debuff_type);
}


void check_individual_effect_timer_joker(int i)
{
    powerup_joker_effect_types joker_type = std::get<powerup_joker_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_joker(joker_type);
}


//----------------------------------------------------------------------------------------------------
void draw_timer(sf::RenderWindow &main_window)
{
    for (int i = 0; i < cooldown_bars.size(); i++)
    {
        cooldown_bars[i].y = SCREENSIZE_Y - 50 - (i * (TIMER_HEIGHT + 10));
        if (cooldown_bars[i].timer_active)
        {
            // time since the timer started
            float elapsed = cooldown_bars[i].powerup_clock.getElapsedTime().asSeconds();
            // time left before the timer expires
            float remaining = cooldown_bars[i].duration - elapsed;

            if (remaining <= 0)
            {
                // WHEN TIMER RUNS OUT
                cooldown_bars[i].timer_active = false;
                if (!cooldown_bars[i].timer_active)
                {
                    if(cooldown_bars[i].powerup_effect.index() == 0)
                    {
                        check_individual_effect_timer_buff(i);
                    }
                    else if(cooldown_bars[i].powerup_effect.index() == 1)
                    {
                        check_individual_effect_timer_debuff(i);
                    }
                    else if (cooldown_bars[i].powerup_effect.index() == 2)
                    {
                        check_individual_effect_timer_joker(i);
                    }
                }
                cooldown_bars.erase(cooldown_bars.begin() + i);
                i--;
                continue;
            }

            // calculates how much of the timer bar should still be visible based on time left
            float percentage = remaining / cooldown_bars[i].duration;
            float new_width = cooldown_bars[i].width * percentage;

            // resizes the width of the bar to reflect the remaining time
            sf::RectangleShape& bar = cooldown_bars[i].graphic;
            bar.setSize(sf::Vector2f(new_width, cooldown_bars[i].len));

            // to keep left side fixed, set origin to left edge and adjust position
            bar.setOrigin(0, 0);
            bar.setPosition(cooldown_bars[i].x, cooldown_bars[i].y);

            main_window.draw(bar);
        }
    }
}
