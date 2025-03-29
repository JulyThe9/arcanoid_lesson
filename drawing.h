void DrawPlat(sf::RenderWindow &app, sf::RectangleShape plat)
{
    app.draw(plat);
}

void DrawBarrier(sf::RenderWindow &app, sf::RectangleShape barrier)
{
    app.draw(barrier);
}

void DrawBall(sf::RenderWindow &app, sf::CircleShape ball)
{
    app.draw(ball);
}

void DrawStatusBar(sf::RenderWindow &app, sf::RectangleShape status_bar)
{
    app.draw(status_bar);
}

void DrawStatusBarLogo(sf::RenderWindow &app, sf::RectangleShape status_bar_logo)
{
    app.draw(status_bar_logo);
}

void DrawScore(sf::RenderWindow &app)
{
    app.draw(score);
}

void DrawBlocks(sf::RenderWindow &app)
{
    for (int i = 0; i < block_rows; i++)
    {
        for(int j = 0; j < block_columns; j++)
        {
            app.draw(curr_gamestate.blocks_graphics[i][j]);
        }
    }
}

void DrawHearts(sf::RenderWindow &app)
{
    for(int i = 0; i < lives_amount; i++)
    {
        app.draw(vector_graphics_life[i]);
    }
}

void DrawGameWonText(sf::RenderWindow &app)
{
    app.draw(game_won_text);
}

void DrawNoHeartsText(sf::RenderWindow &app)
{
    app.draw(no_hearts_text);
}

void DrawHeartDeductionText(sf::RenderWindow &app)
{
    app.draw(heart_deduction_text);
}
