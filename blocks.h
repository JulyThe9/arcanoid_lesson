void init_block()
{
    block = sf::RectangleShape(sf::Vector2f(main_block.block_width, main_block.block_len));

    block.setFillColor(sf::Color(500, 30, 320));

    block.setPosition(main_block.blockX, main_block.blockY);
}
