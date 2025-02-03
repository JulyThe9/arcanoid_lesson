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
        case COLLISION_CASE_BOTTOM:
            if (recent_posX > current_posX)
            {
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case COLLISION_CASE_RIGHT:
            if (recent_posY < current_posY)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case COLLISION_CASE_TOP:
            if (recent_posX < current_posX)
            {
                alpha_x = alpha_x * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }

        case COLLISION_CASE_LEFT:
            if (recent_posY > current_posY)
            {
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            else
            {
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
        //right side of platform
        case COLLISION_CASE_PLATFORM_RIGHT:
            //ball flies right to left
            if(recent_posX >= current_posX)
            {
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
        //left side of platform
        case COLLISION_CASE_PLATFORM_LEFT:
            //ball flies right to left
            if (recent_posX >= current_posX)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                current_posX = recent_posX;
                current_posY = recent_posY;
                return;
            }
    }
}
