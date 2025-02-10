sf::RectangleShape init_platform()
{
    sf::RectangleShape platform(sf::Vector2f(gs.plat_width, plat_len));

    platform.setPosition(platX, platY);

    return platform;
}
