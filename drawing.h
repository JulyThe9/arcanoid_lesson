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
