sf::RectangleShape init_logo()
{
    sf::RectangleShape status_bar_logo = sf::RectangleShape(sf::Vector2f(logo.width,
                                                                         logo.length));

    status_bar_logo.setTexture(&arcanoid_logo);

    status_bar_logo.setPosition(logo.x, logo.y);

    return status_bar_logo;
}
