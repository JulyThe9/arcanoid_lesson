sf::RectangleShape init_platform()
{
    sf::RectangleShape platform(sf::Vector2f(curr_gamestate.platform.width,
                                             curr_gamestate.platform.len));
    platform.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);

    return platform;
}

sf::RectangleShape init_barrier()
{
    sf::RectangleShape barrier(sf::Vector2f(barrier_obj.width, barrier_obj.length));

    barrier.setFillColor(sf::Color(200, 0, 0));

    barrier.setPosition(barrier_obj.x, barrier_obj.y);

    return barrier;
}

sf::CircleShape init_ball()
{
    sf::CircleShape ball(curr_gamestate.ball.size_radius);

    ball.setFillColor(sf::Color(150, 250, 50));

    ball.setPosition(curr_gamestate.ball.curr_x, curr_gamestate.ball.curr_y);

    return ball;
}

sf::RectangleShape init_block(block_type &current_block)
{
    sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(BLOCK_WIDTH, BLOCK_LEN));

    block.setTexture(&current_block.texture);

    block.setTextureRect(sf::IntRect(0, 0, BLOCK_WIDTH, BLOCK_LEN));

    block.setPosition(current_block.blockX, current_block.blockY);

    return block;
}

sf::RectangleShape init_status_bar()
{
    sf::RectangleShape status_bar = sf::RectangleShape(sf::Vector2f(status_bar_width, status_bar_length));

    status_bar.setTexture(&background_status_bar);

    status_bar.setPosition(0, 0);

    return status_bar;
}

sf::RectangleShape init_logo()
{
    sf::RectangleShape status_bar_logo = sf::RectangleShape(sf::Vector2f(logo.width,logo.length));

    status_bar_logo.setTexture(&arcanoid_logo);

    status_bar_logo.setPosition(logo.x, logo.y);

    return status_bar_logo;
}

sf::RectangleShape init_heart(lives_type &current_life, int heart_index)
{
    sf::RectangleShape status_bar_heart = sf::RectangleShape(sf::Vector2f(vector_life_data[heart_index].width,
                                                                          vector_life_data[heart_index].length));
    status_bar_heart.setTexture(&current_life.texture);

    status_bar_heart.setPosition(current_life.x, current_life.y);

    return status_bar_heart;
}
