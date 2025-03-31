void DrawPlat(sf::RenderWindow &main_window, sf::RectangleShape plat)
{
    main_window.draw(plat);
}

void DrawBarrier(sf::RenderWindow &main_window, sf::RectangleShape barrier)
{
    main_window.draw(barrier);
}

void DrawBall(sf::RenderWindow &main_window, sf::CircleShape ball)
{
    main_window.draw(ball);
}

void DrawStatusBar(sf::RenderWindow &main_window, sf::RectangleShape status_bar)
{
    main_window.draw(status_bar);
}

void DrawStatusBarLogo(sf::RenderWindow &main_window, sf::RectangleShape status_bar_logo)
{
    main_window.draw(status_bar_logo);
}

void DrawScore(sf::RenderWindow &main_window)
{
    main_window.draw(score);
}

void DrawBlocks(sf::RenderWindow &main_window)
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            main_window.draw(curr_gamestate.blocks_graphics[i][j]);
        }
    }
}

void DrawHearts(sf::RenderWindow &main_window)
{
    for(int i = 0; i < lives_amount; i++)
    {
        main_window.draw(vector_graphics_life[i]);
    }
}

void DrawGameWonText(sf::RenderWindow &main_window)
{
    main_window.draw(game_won_text);
}

void DrawNoHeartsText(sf::RenderWindow &main_window)
{
    main_window.draw(no_hearts_text);
}

void DrawHeartDeductionText(sf::RenderWindow &main_window)
{
    main_window.draw(heart_deduction_text);
}
