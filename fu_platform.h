
sf::RectangleShape init_platform()
{
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

    sf::RectangleShape platform(sf::Vector2f(plat_width, plat_len));

    platform.setPosition(platX, platY);

    return platform;
}
