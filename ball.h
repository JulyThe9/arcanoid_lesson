/**
*@file ball.h
*@brief contains all ball directions

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


/**
*@brief gets new x coordinate of ball for every frame

*@param agr_deg the degrees of the balls flight

*@return all added pixels to the balls x position
*/
float get_new_x(float agr_deg)
{
    return curr_gamestate.ball.speed * sin(agr_deg * (M_PI / 180.0));
}

/**
*@brief gets new y coordinate of ball for every frame

*@param agr_deg the degrees of the balls flight

*@return all added pixels to the balls x position
*/
float get_new_y(float agr_deg)
{
    return curr_gamestate.ball.speed * cos(agr_deg * (M_PI / 180.0));
}

//-------------------------------------------------------------------
/**
*@brief handles direction of balls flight

*@param wall_side if it hit right, left, bottom or top

*@return returns once found out what its new direction is
*/
void handle_collision(char wall_side)
{
    alpha_x = get_new_x(curr_degrees);
    alpha_y = get_new_y(curr_degrees);

    switch (wall_side)
    {
        case COLLISION_CASE_BOTTOM:
            if (curr_gamestate.ball.curr_x > curr_gamestate.ball.recent_x)
            {
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }

        case COLLISION_CASE_RIGHT:
            if (curr_gamestate.ball.curr_y < curr_gamestate.ball.recent_y)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            else if(curr_gamestate.ball.curr_y > curr_gamestate.ball.recent_y)
            {
                alpha_x = alpha_x * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }

        case COLLISION_CASE_TOP:
            if (curr_gamestate.ball.curr_x <= curr_gamestate.ball.recent_x)
            {
                alpha_x = alpha_x * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            else
            {
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }

        case COLLISION_CASE_LEFT:
            if (curr_gamestate.ball.curr_y > curr_gamestate.ball.recent_y)
            {
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            else
            {
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
        //right side of platform
        case COLLISION_CASE_PLATFORM_RIGHT:
            //ball flies right to left
            if(curr_gamestate.ball.curr_x >= curr_gamestate.ball.recent_x)
            {
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
        //left side of platform
        case COLLISION_CASE_PLATFORM_LEFT:
            //ball flies right to left
            if (curr_gamestate.ball.curr_x >= curr_gamestate.ball.recent_x)
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
            //ball flies left to right
            else
            {
                alpha_x = alpha_x * (-1);
                alpha_y = alpha_y * (-1);
                curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
                curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
                return;
            }
        case COLLISION_CASE_RESET:
            curr_gamestate.ball.recent_x = curr_gamestate.ball.curr_x;
            curr_gamestate.ball.recent_y = curr_gamestate.ball.curr_y;
            return;
    }
}
