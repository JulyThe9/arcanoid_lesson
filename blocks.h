void init_block(block_type current_block)
{
    block = sf::RectangleShape(sf::Vector2f(current_block.block_width, current_block.block_len));

    block.setFillColor(sf::Color(500, 30, 320));

    block.setPosition(current_block.blockX, current_block.blockY);

    cout << "PosX: " << current_block.blockX << "; PosY: " << current_block.blockY << endl;
}
