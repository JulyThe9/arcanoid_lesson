sf::RectangleShape init_logo()
{
    sf::RectangleShape status_bar_logo = sf::RectangleShape(sf::Vector2f(logo_width, logo_length));

    status_bar_logo.setTexture(&arcanoid_logo);

    status_bar_logo.setPosition(logo_posX, logo_posY);

    return status_bar_logo;
}
