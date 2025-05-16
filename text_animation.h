/**
*@file text_animation.h
*@brief all game text initializations and blinking logic

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


/**
*@brief sets game won text

*game won text once all blocks are gone, called in hit_block()
*/
void set_game_won()
{
    game_won_text.setFont(font);
    game_won_text.setCharacterSize(50);
    game_won_text.setFillColor(sf::Color::Green);
    game_won_text.setStyle(sf::Text::Bold);
    game_won_text.setPosition(280, 700);
    game_won_text.setString("CONGRADULATIONS! YOU WON!");
    game_status = BLOCKS_GONE;
}

/**
*@brief sets game loss text

*game loss text once all lives are gone, called in hit_barrier()


*@param heart_number current heart number necessary to fill that space with empty heart texture;
*/
void set_game_loss(int heart_number)
{
    vector_life_data[heart_number].texture = heart_texture_empty;
    no_hearts_text.setFont(font);
    no_hearts_text.setCharacterSize(70);
    no_hearts_text.setFillColor(sf::Color::Red);
    no_hearts_text.setStyle(sf::Text::Bold);
    no_hearts_text.setPosition(SCREENSIZE_X / 2 - 200, 700);
    no_hearts_text.setString("Game Over!");
    game_status = HEARTS_GONE;
}


/**
*@brief sets loss of life text

*game loss of life text once one life has been removed, but not all. Called in hit_barrier()


*@param heart_number current number of heart necessary to fill that space with empty heart texture;
*/

void set_loss_of_life(int &heart_number)
{
    vector_life_data[heart_number].texture = heart_texture_empty;
    heart_deduction_text.setFont(font);
    heart_deduction_text.setCharacterSize(50);
    heart_deduction_text.setFillColor(sf::Color::Yellow);
    heart_deduction_text.setStyle(sf::Text::Bold);
    heart_deduction_text.setPosition(SCREENSIZE_X / 2 - 300, 700);
    heart_deduction_text.setString("Press Space to continue..");
    game_status = HEART_DEDUCTION;
    heart_number--;
}
/*
void set_countdown_three()
{
    countdown_three.setFont(font);
    countdown_three.setCharacterSize(50);
    countdown_three.setFillColor(sf::Color::Green);
    countdown_three.setStyle(sf::Text::Bold);
    countdown_three.setPosition(SCREENSIZE_X / 2 - 150, 700);
    countdown_three.setString("3");
    game_status = COUNTDOWN_THREE;
}

void set_countdown_two()
{
    countdown_two.setFont(font);
    countdown_two.setCharacterSize(50);
    countdown_two.setFillColor(sf::Color::Yellow);
    countdown_two.setStyle(sf::Text::Bold);
    countdown_two.setPosition(SCREENSIZE_X / 2 - 150, 700);
    countdown_two.setString("2");
    game_status = COUNTDOWN_TWO;
}

void set_countdown_one()
{
    countdown_one.setFont(font);
    countdown_one.setCharacterSize(50);
    countdown_one.setFillColor(sf::Color::Red);
    countdown_one.setStyle(sf::Text::Bold);
    countdown_one.setPosition(SCREENSIZE_X / 2 - 150, 700);
    countdown_one.setString("1");
    game_status = GAME_ACTIVE;
}
*/

/**
*@brief handles animations of texts like game loss text or loss of life text

*cycles betwean visible and invisible period through timePassed

*@param lastTime last timestamp
*@param curTime current timestamp
*@param timePassed time that has passed betwean those two
*/
void text_animation(std::chrono::time_point<std::chrono::high_resolution_clock> &lastTime,
                   std::chrono::time_point<std::chrono::high_resolution_clock> &curTtime,
                   std::chrono::milliseconds &timePassed)
{
    // text visible case
    if (text_visible)
    {
        // text has has been visible for a time long enough,
        // make it hidden
        if (timePassed.count() > TEXT_VISIBLE_PERIOD)
        {
#ifdef DEBUG
            cout << "-------------BLINK HIDDEN------------" << endl;
            cout << timePassed.count() << " ms passed, making text HIDDEN\n";
#endif
            heart_deduction_text.setFillColor(sf::Color::Black);
            no_hearts_text.setFillColor(sf::Color::Black);
            text_visible = false;
            lastTime = curTtime;
        }
    }
    // text invisible case
    else
    {
        // text has has been hidden for a time long enough,
        // make it visible
        if (timePassed.count() > TEXT_NOT_VISIBLE_PERIOD)
        {
#ifdef DEBUG
            cout << "-------------BLINK VISIBLE-----------" << endl;
            cout << timePassed.count() << " ms passed, making text VISIBLE\n";
#endif
            heart_deduction_text.setFillColor(sf::Color::Yellow);
            no_hearts_text.setFillColor(sf::Color::Red);
            text_visible = true;
            lastTime = curTtime;
        }
    }
}

std::chrono::milliseconds countdown_animation(std::chrono::time_point<std::chrono::high_resolution_clock> &lastTime,
                        std::chrono::time_point<std::chrono::high_resolution_clock> &curTtime,
                        std::chrono::milliseconds &timePassed)
{
    if (timePassed.count() > TEXT_VISIBLE_PERIOD)
        {
            lastTime = curTtime;
        }
    return timePassed;
}
