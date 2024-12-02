int get_new_angle()
{
    curr_degrees = 0;
    float degree_adder = 0.57;
    float plat_pos = temp_x - platX;

    float plat_pos_perc = (100.0 / plat_width) * plat_pos;
    cout << "plat_pos: " << plat_pos << endl;
    cout << "plat_width: " << plat_width << endl;
    cout << "plat_pos_perc: " << plat_pos_perc << endl;


    if (temp_x > platX && temp_x < platX + plat_width / 2)
    {
        cout << "left" << "; plat_pos: " << plat_pos
        << "; angle: " << ((360/plat_width) * plat_pos_perc) << "; plat_pos_perc: " << plat_pos_perc << endl;

        return ((360 / 100) * plat_pos_perc) - 135;
    }
    else if (temp_x > platX + plat_width / 2 && temp_x < platX + plat_width)
    {
        cout << "right" << "; plat_pos: " << plat_pos
        << "; angle: " << (((360.0 / 100.0) * plat_pos_perc) - 135) << "; plat_pos_perc: " << plat_pos_perc << endl;
        return (((360.0 / 100.0) * plat_pos_perc) - 135);
    }
}
