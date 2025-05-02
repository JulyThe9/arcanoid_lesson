/**
*@file get_new_angle.h
*@brief calculates new angle of ball if hit platform(different for every section of platform)

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


/**
*@brief gets new angle of ball after hitting platform

*calculates each section of platform and gives back appropriate angle for current section, that ball hit

*@return curr_degrees the new degrees of balls flight
*/
int get_new_angle()
{
    curr_degrees = 0;
    float plat_pos = 0.0;
    int sections_per_side = 20;

    if(curr_gamestate.ball.curr_x - curr_gamestate.platform.x + curr_gamestate.ball.size_radius > curr_gamestate.platform.width / 2)
    {
        plat_pos = curr_gamestate.ball.curr_x - curr_gamestate.platform.x;
    }
    else if(curr_gamestate.ball.curr_x - curr_gamestate.platform.x + curr_gamestate.ball.size_radius <= curr_gamestate.platform.width / 2)
    {
        plat_pos = curr_gamestate.ball.curr_x - curr_gamestate.platform.x + curr_gamestate.ball.size_radius;
    }

    float plat_posr = curr_gamestate.ball.curr_x - curr_gamestate.platform.x;
    double section = curr_gamestate.platform.width / (sections_per_side * 2.0);
    int deg_per_section = 90 / (sections_per_side + 1);

    //right side
    if(plat_posr > (curr_gamestate.platform.width / 2))
    {
        for(int i = 0; i < sections_per_side; i++)
        {
            if(plat_posr > (curr_gamestate.platform.width / 2) + (section * i) && plat_posr < (curr_gamestate.platform.width / 2) + section * (i + 1))
            {
                curr_degrees = (deg_per_section * (i + 1));
                handle_collision(COLLISION_CASE_PLATFORM_RIGHT);
            }
        }
    }
    //left side
    else
    {
        for(int i = 0; i < sections_per_side; i++)
        {
            if(plat_pos < (curr_gamestate.platform.width / 2) - (section * i) && plat_pos > (curr_gamestate.platform.width / 2) - section * (i + 1))
            {
                curr_degrees = (deg_per_section * (i + 1));
                handle_collision(COLLISION_CASE_PLATFORM_LEFT);
            }
        }
    }

#ifdef DEBUG
            cout << "-------NEWLY CALCULATED ANGLE--------" << endl;
            cout << "current ball pos: " << curr_gamestate.ball.curr_x << " | " << curr_gamestate.ball.curr_y + curr_gamestate.ball.size_radius << endl;
            cout << "new curr_degrees: " << curr_degrees << endl;
#endif
    return curr_degrees;
}
