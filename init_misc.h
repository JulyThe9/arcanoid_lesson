/**
*@file init_misc.h
*@brief loading of all fonts and png images

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


/**
*@brief initialization of textures
*/
void init_textures()
{
    if (!texture_ice.loadFromFile("textures/blocks/block_regular_1.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_regular_1.png");
    }
    else if (!texture_poison.loadFromFile("textures/blocks/block_regular_2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_regular_2.png");
    }
    else if(!texture_dirt.loadFromFile("textures/blocks/block_dirt.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_dirt.png");
    }
    else if(!texture_dirt2.loadFromFile("textures/blocks/block_dirt2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_dirt2.png");
    }
    else if(!texture_explosion_small.loadFromFile("textures/blocks/block_explosive.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_dirt2.png");
    }
    else if(!texture_explosion_large.loadFromFile("textures/blocks/block_explosive2.png", sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/blocks/block_explosive2.png");
    }
    else if(!background_status_bar.loadFromFile("textures/status_bar/status_bar_background.png", sf::IntRect(0, 0, status_bar_width, status_bar_length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/status_bar/status_bar_background.png");
    }
    else if(!arcanoid_logo.loadFromFile("textures/status_bar/arcanoid_logo.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/status_bar/arcanoid_logo.png");
    }
    else if(!heart_texture_full.loadFromFile("textures/status_bar/heart_full.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/status_bar/heart_full.png");
    }
    else if(!heart_texture_empty.loadFromFile("textures/status_bar/heart_empty.png", sf::IntRect(0, 0, logo.width, logo.length)))
    {
        // Handle error
        throw std::runtime_error("Failed to load texture: textures/status_bar/heart_empty.png");
    }
}


void init_sounds()
{
    if (!buffer_dirt.loadFromFile("sounds/dirt_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/dirt_sound.wav");
    }
    else if (!buffer_ice.loadFromFile("sounds/ice_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/ice_sound.wav");
    }
    else if (!buffer_poison.loadFromFile("sounds/poison_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/poison_sound.wav");
    }
    else if (!buffer_explosion.loadFromFile("sounds/explosion_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/explosion_sound.wav");
    }
    else if (!buffer_wall.loadFromFile("sounds/wall_hit_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/wall_hit_sound.wav");
    }
    else if (!buffer_platform.loadFromFile("sounds/dirt_sound.wav"))
    {
        throw std::runtime_error("Failed to load audio: sounds/dirt_sound.wav");
    }
}
