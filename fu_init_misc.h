void init_textures()
{
    texture_ice.loadFromFile("textures/blocks/block_regular_1.png", sf::IntRect(0, 0, 90, 30));
    texture_poison.loadFromFile("textures/blocks/block_regular_2.png", sf::IntRect(0, 0, 90, 30));
}

void init_score()
{
    if (!font.loadFromFile("fonts/ArialCEBoldItalic.ttf"))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: bank-gothic-font.ttf");
    }

    score_text.setFont(font);
    score_text.setString("SCORE:");
    score_text.setCharacterSize(50);
    score_text.setFillColor(sf::Color::Red);
    score_text.setStyle(sf::Text::Bold);
    score_text.setPosition(30, 20);

    score.setFont(font);
    score.setString(score_number);
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(235, 20);
}

