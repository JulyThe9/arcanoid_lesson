sf::RectangleShape init_status_bar()
{
    sf::RectangleShape status_bar = sf::RectangleShape(sf::Vector2f(status_bar_width, status_bar_length));

    status_bar.setTexture(&background_status_bar);

    status_bar.setPosition(0, 0);

    return status_bar;
}
