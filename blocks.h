sf::RectangleShape init_block(block_type &current_block)
{
    sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(BLOCK_WIDTH, BLOCK_LEN));

    block.setTexture(&current_block.texture);

    block.setTextureRect(sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN));

    block.setPosition(current_block.blockX, current_block.blockY);

    return block;
}
