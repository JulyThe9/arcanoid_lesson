sf::RectangleShape init_heart(lives_type &current_life, int heart_index)
{
    sf::RectangleShape status_bar_heart = sf::RectangleShape(sf::Vector2f(vector_life_data[heart_index].width,
                                                                          vector_life_data[heart_index].length));
    status_bar_heart.setTexture(&current_life.texture);

    status_bar_heart.setPosition(current_life.x, current_life.y);

    return status_bar_heart;
}
