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
/*
void draw_countdown_three(sf::RenderWindow &main_window)
{
    main_window.draw(countdown_three);
}

void draw_countdown_two(sf::RenderWindow &main_window)
{
    main_window.draw(countdown_two);
}

void draw_countdown_one(sf::RenderWindow &main_window)
{
    main_window.draw(countdown_one);
}
*/

void draw_powerup(sf::RenderWindow &main_window)
{
    for(int i = 0; i < powerups.size(); i++)
    {
        if(powerups[i].powerup_active)
        {
            float time;

            if(powerups[i].first_activation)
            {
                powerups[i].powerup_clock.restart();
                time = 0;
                powerups[i].first_activation = false;
            }
            else
            {
                time = powerups[i].powerup_clock.restart().asSeconds();
            }

            sf::Vector2f position = powerups[i].graphic.getPosition();

            position.y += powerups[i].powerupSpeed * time;
            powerups[i].graphic.setPosition(position);

            main_window.draw(powerups[i].graphic);
        }
        else
        {
            powerups[i].first_activation = true;
        }
    }
}

void draw_timer(sf::RenderWindow &main_window)
{
    for (int i = 0; i < timers.size(); i++)
    {
        if (timers[i].timer_active)
        {
            float elapsed = timers[i].powerup_clock.getElapsedTime().asSeconds();
            float remaining = timers[i].duration - elapsed;

            if (remaining <= 0)
            {
                timers[i].timer_active = false;
                continue;
            }

            // Shrink timer from left to right
            float percentage = remaining / timers[i].duration;
            float new_width = timers[i].width * percentage;

            sf::RectangleShape& bar = timers[i].graphic;
            bar.setSize(sf::Vector2f(new_width, timers[i].len));

            // To keep left side fixed, set origin to left edge and adjust position
            bar.setOrigin(0, 0);
            bar.setPosition(timers[i].x, timers[i].y);

            main_window.draw(bar);
        }
    }
}
