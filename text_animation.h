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


void set_countdown_three()
{
    countdown_three.setFont(font);
    countdown_three.setCharacterSize(100);
    countdown_three.setFillColor(sf::Color::Yellow);
    countdown_three.setStyle(sf::Text::Bold);
    countdown_three.setPosition(SCREENSIZE_X / 2, 700);
    countdown_three.setString("3");
    curr_countdown_num = COUNTDOWN_THREE;
}

void set_countdown_two()
{
    countdown_two.setFont(font);
    countdown_two.setCharacterSize(100);
    countdown_two.setFillColor(sf::Color::Yellow);
    countdown_two.setStyle(sf::Text::Bold);
    countdown_two.setPosition(SCREENSIZE_X / 2, 700);
    countdown_two.setString("2");
    curr_countdown_num = COUNTDOWN_TWO;
}

void set_countdown_one()
{
    countdown_one.setFont(font);
    countdown_one.setCharacterSize(100);
    countdown_one.setFillColor(sf::Color::Yellow);
    countdown_one.setStyle(sf::Text::Bold);
    countdown_one.setPosition(SCREENSIZE_X / 2, 700);
    countdown_one.setString("1");
    curr_countdown_num = COUNTDOWN_ONE;
}


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
    if (user_status_text_visible)
    {
        // text has has been visible for a time long enough,
        // make it hidden
        if (timePassed.count() > TEXT_VISIBLE_PERIOD)
        {
#ifdef DEBUG
            cout << "-------------BLINK HIDDEN------------" << endl;
            cout << timePassed.count() << " ms passed, making text HIDDEN\n";
#endif
            user_status_text_visible = false;
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
            user_status_text_visible = true;
            lastTime = curTtime;
        }
    }
}


void platform_prediction_animation(auto prediction_total_passed_time)
{
    if(prediction_total_passed_time.count() / 10 % PLATFORM_PREDICTION_BLINK_PERIOD < (PLATFORM_PREDICTION_BLINK_PERIOD / 2))
    {
        is_trajectory_prediction_shown = false;
    }
    else
    {
        is_trajectory_prediction_shown = true;
    }
}


void countdown_animation(std::chrono::time_point<std::chrono::high_resolution_clock> &curTtime)
{
    auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(curTtime - countdown_start_time);

    if (timePassed.count() >= COUNTDOWN_PERIOD * 3 && countdown_active)
    {
        cout << "time: " << timePassed.count() << endl;
        play_game_continue_sound();
        countdown_active = false;
        return;
    }
    else if (timePassed.count() >= COUNTDOWN_PERIOD * 2 && countdown_active)
    {
        if (curr_countdown_num != COUNTDOWN_ONE)
        {
            set_countdown_one();
            play_countdown_sound();
        }
    }
    else if (timePassed.count() >= COUNTDOWN_PERIOD&& countdown_active)
    {
        if (curr_countdown_num != COUNTDOWN_TWO)
        {
            set_countdown_two();
            play_countdown_sound();
        }
    }
    else
    {
        if (curr_countdown_num != COUNTDOWN_THREE)
        {
            set_countdown_three();
        }
    }
}
