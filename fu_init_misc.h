void init_textures()
{
    if (!texture_ice.loadFromFile("textures/blocks/block_regular_1.png", sf::IntRect(0, 0, 90, 30)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_regular_1.png");
    }
    else if (!texture_poison.loadFromFile("textures/blocks/block_regular_2.png", sf::IntRect(0, 0, 90, 30)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_regular_2.png");
    }
    else if(!texture_dirt.loadFromFile("textures/blocks/block_dirt.png", sf::IntRect(0, 0, 90, 30)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_dirt.png");
    }
    else if(!texture_dirt2.loadFromFile("textures/blocks/block_dirt2.png", sf::IntRect(0, 0, 90, 30)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_dirt2.png");
    }
}

void init_score()
{
    if (!font.loadFromFile("fonts/ArialCEBoldItalic.ttf"))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: bank-gothic-font.ttf");
    }

    score.setFont(font);
    score.setString(gs.score_number);
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(screensizeX - 200, 20);
}

