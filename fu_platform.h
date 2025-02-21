sf::RectangleShape init_platform()
{
    sf::RectangleShape platform(sf::Vector2f(curr_gamestate.plat_width, plat_len));

    platform.setPosition(platX, platY);

    return platform;
}
