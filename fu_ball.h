sf::CircleShape init_ball()
{
    sf::CircleShape ball(ball_size);

    ball.setFillColor(sf::Color(150, 250, 50));

    ball.setPosition(current_posX, current_posY);

    return ball;
}

//-------------------------------------------------------------------
float get_new_x(float agr_deg)
{
    return curr_gamestate.ball_speed * sin(agr_deg * (M_PI / 180.0));
}

//-------------------------------------------------------------------
float get_new_y(float agr_deg)
{
    return curr_gamestate.ball_speed * cos(agr_deg * (M_PI / 180.0));
}

//-------------------------------------------------------------------
void handle_collision(char wall_side)
{
    alpha_x = get_new_x(curr_degrees);
    alpha_y = get_new_y(curr_degrees);

    switch (wall_side)
    {
        case COLLISION_CASE_BOTTOM:
            if (current_posX > recent_posX)
            {
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }

        case COLLISION_CASE_RIGHT:
            if (current_posY < recent_posY)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }

        case COLLISION_CASE_TOP:
            if (current_posX < recent_posX)
            {
                alpha_x = alpha_x * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            else
            {
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }

        case COLLISION_CASE_LEFT:
            if (current_posY > recent_posY)
            {
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            else
            {
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
        //right side of platform
        case COLLISION_CASE_PLATFORM_RIGHT:
            //ball flies right to left
            if(current_posX >= recent_posX)
            {
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
        //left side of platform
        case COLLISION_CASE_PLATFORM_LEFT:
            //ball flies right to left
            if (current_posX >= recent_posX)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                recent_posX = current_posX;
                recent_posY = current_posY;
                return;
            }
        case COLLISION_CASE_RESET:
            recent_posX = current_posX;
            recent_posY = current_posY;
            return;

    }
}
