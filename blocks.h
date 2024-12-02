sf::RectangleShape init_block(block_type current_block)
{
    sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(current_block.block_width, current_block.block_len));

    block.setFillColor(sf::Color(current_block.colour_red_block, current_block.colour_green_block, current_block.colour_blue_block));

    block.setPosition(current_block.blockX, current_block.blockY);

    return block;
}
