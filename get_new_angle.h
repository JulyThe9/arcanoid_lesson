int get_new_angle()
{
    curr_degrees = 0;
    cout << curr_degrees << endl;
    //plat pos is the position that the ball hits on the platform. plat_pos != temp_x
    float plat_pos = temp_x - platX;
    //percentige of plat_pos
    float plat_pos_perc = (100.0 / plat_width) * plat_pos;
    int section = plat_width / 8;

    if(plat_pos > plat_width / 2 && plat_pos < plat_width / 2 + 35)
    {
        cout << "we are in the first section" << endl;
    }
    else if(plat_pos >= plat_width / 2 + section && plat_pos <= plat_width / 2 + section * 2)
    {
        cout << "we are in the second section" << endl;
    }
    else if(plat_pos > plat_width / 2 + section * 2 && plat_pos <= plat_width / 2 + section * 3)
    {
        cout << "we are in the third section" << endl;
    }
    else if(plat_pos > plat_width / 2 + section * 3 && plat_pos <= plat_width / 2 + section * 4)
    {
        cout << "we are in the fourth section" << endl;
    }
    return 45;
}
