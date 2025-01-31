int get_new_angle()
{
    curr_degrees = 0;
    float plat_posl = 0.0;
    int sections_per_side = 20;
    //plat pos is the position that the ball hits on the platform. plat_pos != temp_x

    //one plat_pos covers the middle, the other covers the far left side of platform, if we dont have it, one of the two flies through.
    //if we dont have it, one of the two flies through.
    if(temp_x - platX + ball_size > plat_width / 2)
    {
        plat_posl = temp_x - platX;
    }
    else if(temp_x - platX + ball_size <= plat_width / 2)
    {
        plat_posl = temp_x - platX + ball_size;
    }
    float plat_posr = temp_x - platX;
    //percentige of plat_pos
    double section = plat_width / (sections_per_side * 2.0);
    int deg_per_section = 90 / (sections_per_side + 1);

    //right side
    if(plat_posr > (plat_width / 2))
    {
        for(int i = 0; i < sections_per_side; i++)
        {
            /*
            cout << "section: " << section << "; sections per side: " << sections_per_side << endl;
            cout << "plat_width / 2: " << plat_width / 2 << endl;
            cout << "plat_pos left: " << plat_posl << endl;
            cout << "plat_pos right: " << plat_posr << endl;
            cout << "section * i: " << section * i << endl;
            cout << "calculation1: " << (plat_width / 2) + (section * i) << endl;
            cout << "(plat_width / (sections_per_side * 2)): " << (plat_width / (sections_per_side * 2)) << endl;
            cout << "calculation 2: " << (plat_width / 2) + ((plat_width / (sections_per_side * 2)) * (i + 1)) << endl;
            cout << "plat_pos > (plat_width / 2) + (section * i) && plat_pos < (plat_width / 2) + ((plat_width / (sections_per_side * 2)) * (i + 1))" << endl;
            cout << "-----------------------------" << endl;
            */

            if(plat_posr > (plat_width / 2) + (section * i) && plat_posr < (plat_width / 2) + section * (i + 1))
            {
                curr_degrees = (deg_per_section * (i + 1));
                handle_collision('u');
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

            if(plat_posl < (plat_width / 2) - (section * i) && plat_posl > (plat_width / 2) - section * (i + 1))
            {
                curr_degrees = (deg_per_section * (i + 1));
                handle_collision('o');
            }
        }
    }
    return curr_degrees;
}

/*
cout << "plat_pos: " << plat_pos << endl;
cout << "plat_width: " << plat_width << endl;
cout << "sections_per_side: " << sections_per_side << endl;
cout << "deg_per_section: " << deg_per_section << endl;
cout << "rechnung 1: " << (plat_width / 2) + (sections_per_side * i) << endl;
cout << "rechnung 2: " << (plat_width / 2) + ((plat_width / (sections_per_side * 2)) * (i + 1)) << endl;
cout << "curr_deg: " << curr_degrees << endl;
*/
