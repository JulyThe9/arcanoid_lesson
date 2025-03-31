void SetGameWon()
{
    game_won_text.setFont(font);
    game_won_text.setCharacterSize(50);
    game_won_text.setFillColor(sf::Color::Green);
    game_won_text.setStyle(sf::Text::Bold);
    game_won_text.setPosition(280, 700);
    game_won_text.setString("CONGRADULATIONS! YOU WON!");
    game_status = BLOCKS_GONE;
}

void SetGameLoss(int heart_number)
{
    vector_life_data[heart_number].heart_texture = heart_texture_empty;
    no_hearts_text.setFont(font);
    no_hearts_text.setCharacterSize(70);
    no_hearts_text.setFillColor(sf::Color::Red);
    no_hearts_text.setStyle(sf::Text::Bold);
    no_hearts_text.setPosition(SCREENSIZE_X / 2 - 200, 700);
    no_hearts_text.setString("Game Over!");
    game_status = HEARTS_GONE;
}

void SetLossOfLife(int &heart_number)
{
    vector_life_data[heart_number].heart_texture = heart_texture_empty;
    heart_deduction_text.setFont(font);
    heart_deduction_text.setCharacterSize(50);
    heart_deduction_text.setFillColor(sf::Color::Yellow);
    heart_deduction_text.setStyle(sf::Text::Bold);
    heart_deduction_text.setPosition(SCREENSIZE_X / 2 - 300, 700);
    heart_deduction_text.setString("Press Space to continue..");
    game_status = HEART_DEDUCTION;
    heart_number--;
}

void TextAnimation(std::chrono::time_point<std::chrono::high_resolution_clock> &lastTime,
                   std::chrono::time_point<std::chrono::high_resolution_clock> &curTtime,
                   std::chrono::milliseconds &timePassed)
{
    // text visible case
    if (textVisible)
    {
        // text has has been visible for a time long enough,
        // make it hidden
        if (timePassed.count() > TEXT_VISIBLE_PERIOD)
        {
            cout << timePassed.count() << " ms passed, making text HIDDEN\n";
            heart_deduction_text.setFillColor(sf::Color::Black);
            no_hearts_text.setFillColor(sf::Color::Black);
            textVisible = false;
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
            cout << timePassed.count() << " ms passed, making text VISIBLE\n";
            heart_deduction_text.setFillColor(sf::Color::Yellow);
            no_hearts_text.setFillColor(sf::Color::Red);
            textVisible = true;
            lastTime = curTtime;
        }
    }
}
