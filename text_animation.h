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
    no_hearts_text.setPosition(screensizeX / 2 - 200, 700);
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
    heart_deduction_text.setPosition(280, 700);
    heart_deduction_text.setString("Press Space to continue..");
    game_status = HEART_DEDUCTION;
    heart_number--;
}
