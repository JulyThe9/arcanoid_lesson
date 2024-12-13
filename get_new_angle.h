int get_new_angle()
{
    curr_degrees = 0;
    cout << curr_degrees << endl;

    int sections_per_side = 15;
    //plat pos is the position that the ball hits on the platform. plat_pos != temp_x
    float plat_pos = temp_x - platX;
    //percentige of plat_pos
    float plat_pos_perc = (100.0 / plat_width) * plat_pos;
    int section = plat_width / (sections_per_side * 2);
    int deg_per_section = 90 / (sections_per_side + 1);

    //right side
    if(plat_pos > (plat_width / 2))
    {
        for(int i = 0; i < sections_per_side; i++)
        {
            if(plat_pos > (plat_width / 2) + (section * i) && plat_pos < (plat_width / 2) + ((plat_width / (sections_per_side * 2)) * (i + 1)))
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
            if(plat_pos < (plat_width / 2) - (section * i) && plat_pos > (plat_width / 2) - ((plat_width / (sections_per_side * 2)) * (i + 1)))
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
