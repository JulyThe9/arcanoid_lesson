sf::RectangleShape init_barrier()
{
    sf::RectangleShape barrier(sf::Vector2f(barrier_width, barrier_length));

    barrier.setFillColor(sf::Color(200, 0, 0));

    barrier.setPosition(barrierX, barrierY);

    return barrier;
}
