sf::CircleShape init_ball()
{
    sf::CircleShape ball(ball_size);

    ball.setFillColor(sf::Color(150, 250, 50));

    ball.setPosition(recent_posX, recent_posY);

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
            if (recent_posX > curret_posX)
            {
                alpha_y = alpha_y * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case 'r':
            if (recent_posY < current_posY)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case 't':
            if (recent_posX < curret_posX)
            {
                alpha_x = alpha_x * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case 'l':
            if (recent_posY > current_posY)
            {
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_y = alpha_y * (-1);
                curret_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
    }
}
