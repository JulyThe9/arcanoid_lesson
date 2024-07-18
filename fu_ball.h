sf::CircleShape init_ball()
{
    sf::CircleShape ball(ball_size);

    ball.setFillColor(sf::Color(150, 250, 50));

    ball.setPosition(ballX, ballY);

    return ball;
}

//-------------------------------------------------------------------
float get_new_x(float agr_deg)
{
    return ball_speed * sin(agr_deg * (M_PI / 180.0));
}

//-------------------------------------------------------------------
float get_new_y(float agr_deg)
{
    return ball_speed * cos(agr_deg * (M_PI / 180.0));
}

//-------------------------------------------------------------------
void handle_collision(char wall_side)
{
    alpha_x = get_new_x(curr_degrees);
    alpha_y = get_new_y(curr_degrees);

    switch (wall_side)
    {
        case 'b':
            if (ballX > ballX2)
            {
                alpha_y = alpha_y * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }

        case 'r':
            if (ballY < ballY2)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }

        case 't':
            if (ballX < ballX2)
            {
                alpha_x = alpha_x * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }
            else
            {
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }

        case 'l':
            if (ballY > ballY2)
            {
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }
            else
            {
                alpha_y = alpha_y * (-1);
                ballX2 = ballX;
                ballY2 = ballY;
                return;
            }
    }
}
