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

    score.setFont(font);
    score.setInt(10);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(50, 50);
}

