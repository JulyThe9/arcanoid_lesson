void init_textures()
{
    if (!texture_ice.loadFromFile("textures/blocks/block_regular_1.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_regular_1.png");
    }
    else if (!texture_poison.loadFromFile("textures/blocks/block_regular_2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_regular_2.png");
    }
    else if(!texture_dirt.loadFromFile("textures/blocks/block_dirt.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_dirt.png");
    }
    else if(!texture_dirt2.loadFromFile("textures/blocks/block_dirt2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_dirt2.png");
    }
    else if(!texture_explosion_small.loadFromFile("textures/blocks/block_explosive.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_dirt2.png");
    }
    else if(!texture_explosion_large.loadFromFile("textures/blocks/block_explosive2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/blocks/block_explosive2.png");
    }
    else if(!background_status_bar.loadFromFile("textures/status_bar/status_bar_background.png", sf::IntRect(0, 0, status_bar_width, status_bar_length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/status_bar/status_bar_background.png");
    }
    else if(!arcanoid_logo.loadFromFile("textures/status_bar/arcanoid_logo.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/status_bar/arcanoid_logo.png");
    }
    else if(!heart_texture_full.loadFromFile("textures/status_bar/heart_full.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/status_bar/heart_full.png");
    }
    else if(!heart_texture_empty.loadFromFile("textures/status_bar/heart_empty.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load font: textures/status_bar/heart_empty.png");
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
    score.setCharacterSize(60);
    score.setFillColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(SCREENSIZE_X - 300, 25);
    score.setString(curr_gamestate.score_number);
}
