sf::RectangleShape init_platform()
{
    sf::RectangleShape platform(sf::Vector2f(curr_gamestate.platform.width,
                                             curr_gamestate.platform.len));

    platform.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);

    return platform;
}
