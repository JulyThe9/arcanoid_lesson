int get_new_angle()
{
    curr_degrees = 0;

    int sections_per_side = 20;
    //plat pos is the position that the ball hits on the platform. plat_pos != temp_x
    float plat_posl = temp_x - platX + ball_size * 2;
    float plat_posr = temp_x - platX + ball_size;
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
            cout << "plat_pos: " << plat_pos << endl;
            cout << "plat_width / 2: " << plat_width / 2 << endl;
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
            cout << "plat_pos: " << plat_pos << endl;
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
