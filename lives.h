sf::RectangleShape init_lives(lives_type current_life)
{
    sf::RectangleShape life = sf::RectangleShape(sf::Vector2f(current_life.lives_width, current_life.lives_length));

    life.setFillColor(sf::Color(current_life.colour_red_life, current_life.colour_green_life, current_life.colour_blue_life));

    life.setPosition(current_life.livesX, current_life.livesY);

    return life;
}
