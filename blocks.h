
sf::RectangleShape init_block(block_type &current_block)
{
    sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(current_block.block_width, current_block.block_len));

    block.setTexture(&current_block.texture);
    block.setTextureRect(sf::IntRect(0, 0, block_WIDTH, block_LEN));

    block.setPosition(current_block.blockX, current_block.blockY);

    return block;
}
