void create_powerup(int row, int col)
{
    int powerup_generation_chance = (std::rand() % 100);
    if (powerup_generation_chance >= 38)
    {
        falling_powerup_type curr_falling_powerup(0, 0, POWERUP_SPEED, curr_gamestate.blocks[row][col], BUFF);

        powerup_class_types curr_powerup_type = get_weighted_random(powerup_class_map);
        //cout << "type: " << curr_powerup_type << endl;

        if (curr_powerup_type == BUFF)
        {
            powerup_buff_effect_types buff = get_weighted_random(buff_map);
            //cout << "buff: " << buff << endl;
            //cout << "---------" << endl;
        }
        else if (curr_powerup_type == DEBUFF)
        {
            powerup_debuff_effect_types debuff = get_weighted_random(debuff_map);
            //cout << "debuff: " << debuff << endl;
            //cout << "---------" << endl;
        }
        else
        {
            powerup_joker_effect_types joker = get_weighted_random(joker_map);
            //cout << "joker: " << joker << endl;
            //cout << "---------" << endl;
        }

        int curr_powerup_x = curr_gamestate.blocks[row][col].blockX + ((BLOCK_WIDTH - POWERUP_WIDTH) / 2);
        int curr_powerup_y = curr_gamestate.blocks[row][col].blockY;

        curr_falling_powerup = falling_powerup_type(curr_powerup_x,
                                    curr_powerup_y,
                                    POWERUP_SPEED,
                                    curr_gamestate.blocks[row][col],
                                    curr_powerup_type);

        curr_falling_powerup.powerup_active = true;
        falling_powerups.push_back(curr_falling_powerup);
    }
}


void powerup_activity()
{
    for (int i = 0; i < cooldown_bars.size(); i++)
    {
        if (cooldown_bars[i].timer_active)
        {
            if(cooldown_bars[i].powerup_effect.index() == 0)
            {
                powerup_buff_effect_types buff_type = std::get<powerup_buff_effect_types>(cooldown_bars[i].powerup_effect);

                if (buff_type == TRAJECTORY_PREDICTION)
                {
                    is_trajectory_prediction_buff_active = true;
                    cout << "timer started :)" << endl;
                }
            }
            else if(cooldown_bars[i].powerup_effect.index() == 1)
            {
                powerup_debuff_effect_types debuff_type = std::get<powerup_debuff_effect_types>(cooldown_bars[i].powerup_effect);
            }
            else if (cooldown_bars[i].powerup_effect.index() == 2)
            {
                powerup_joker_effect_types joker_type = std::get<powerup_joker_effect_types>(cooldown_bars[i].powerup_effect);

                if (joker_type == PLAT_Y_AXIS)
                {
                    is_plat_y_axis_joker_active = true;
                    cout << "timer started :)" << endl;
                }
            }
        }
    }
}


void handle_deletion_powerup()
{
    for(int i = 0; i < falling_powerups.size(); i++)
    {
        sf::Vector2f position = falling_powerups[i].rectangle.getPosition();
        if(position.y > barrier_obj.y - POWERUP_LEN)
        {
            falling_powerups[i].powerup_active = false;
            falling_powerups.erase(falling_powerups.begin() + i);
        }
    }
}


void reset_powerups()
{
    is_plat_y_axis_joker_active = false;
}
