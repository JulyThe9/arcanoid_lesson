sf::RectangleShape init_block()
{
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

    sf::RectangleShape block(sf::Vector2f(block_width, block_len));

    block.setFillColor(sf::Color(500, 30, 320));

    block.setPosition(blockX, blockY);

    return block;
}

//void conditions(char block_side)
//{

//}
