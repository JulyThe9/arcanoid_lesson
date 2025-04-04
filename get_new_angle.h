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
            /*
            cout << "section: " << section << "; sections per side: " << sections_per_side << endl;
            cout << "plat_pos left: " << plat_posl << endl;
            cout << "plat_pos right: " << plat_posr << endl;
            cout << "plat_width / 2: " << plat_width / 2 << endl;
            cout << "section * i: " << section * i << endl;
            cout << "calculation1: " << (plat_width / 2) - (section * i) << endl;
            cout << "calculation 2: " << (plat_width / 2) - section * (i + 1) << endl;
            cout << "(plat_pos < (plat_width / 2) - (section * i) && plat_pos > (plat_width / 2) - section * (i + 1))" << endl;
            cout << "-----------------------------" << endl;
            */

            if(plat_pos < (curr_gamestate.platform.width / 2) - (section * i) && plat_pos > (curr_gamestate.platform.width / 2) - section * (i + 1))
            {
                curr_degrees = (deg_per_section * (i + 1));
                handle_collision(COLLISION_CASE_PLATFORM_LEFT);
            }
        }
    }
    return curr_degrees;
}
