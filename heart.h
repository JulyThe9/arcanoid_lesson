sf::RectangleShape init_heart(lives_type &current_life)
{
    sf::RectangleShape status_bar_heart = sf::RectangleShape(sf::Vector2f(heart_width, heart_length));

    status_bar_heart.setTexture(&heart_texture);

    status_bar_heart.setPosition(current_life.livesX, current_life.livesY);

    return status_bar_heart;
}
