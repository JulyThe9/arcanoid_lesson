void create_new_timers(std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_spec_powerup, int i)
{
    int pos_x = SCREENSIZE_X - 110;
    int pos_y = SCREENSIZE_Y - 50 - (cooldown_bars.size() * (TIMER_HEIGHT + 10));

    timer_type new_timer(pos_x, pos_y, falling_powerups[i].type, curr_spec_powerup);
    new_timer.timer_active = true;
    cooldown_bars.push_back(new_timer);
}


void does_timer_exist(bool &timer_exists, std::variant<powerup_buff_effect_types, powerup_debuff_effect_types, powerup_joker_effect_types> curr_spec_powerup)
{
    for (int i = 0; i < cooldown_bars.size(); ++i)
    {
        if (cooldown_bars[i].powerup_effect == curr_spec_powerup && cooldown_bars[i].timer_active)
        {
            cooldown_bars[i].powerup_clock.restart();
            timer_exists = true;
            break;
        }
    }
}


void clean_up_timers()
{
    for (int i = 0; i < falling_powerups.size(); i++)
    {
        falling_powerups[i].powerup_active = false;
    }
    for (int i = 0; i < cooldown_bars.size(); i++)
    {
        cooldown_bars[i].timer_active = false;
    }
    cooldown_bars.clear();
}


//----------------------------------------------------------------------------------------------------
void check_specific_effect_timer_buff(powerup_buff_effect_types buff_type)
{
    //check for specific buffs
    if (buff_type == TRAJECTORY_PREDICTION)
    {
        is_trajectory_prediction_buff_active = false;
    }
}


void check_specific_effect_timer_debuff(powerup_debuff_effect_types debuff_type)
{
    //check for specific debuffs
}


void check_specific_effect_timer_joker(powerup_joker_effect_types joker_type)
{
    //check for specific jokers
    if (joker_type == PLAT_Y_AXIS)
    {
        curr_gamestate.platform.y = PLATFORM_INITIAL_Y;
        curr_gamestate.platform.width = PLATFORM_WIDTH;
        is_plat_y_axis_joker_active = false;
    }
}


//---------------------------------
void check_individual_effect_timer_buff(int i)
{
    powerup_buff_effect_types buff_type = std::get<powerup_buff_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_buff(buff_type);
}


void check_individual_effect_timer_debuff(int i)
{
    powerup_debuff_effect_types debuff_type = std::get<powerup_debuff_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_debuff(debuff_type);
}


void check_individual_effect_timer_joker(int i)
{
    powerup_joker_effect_types joker_type = std::get<powerup_joker_effect_types>(cooldown_bars[i].powerup_effect);

    check_specific_effect_timer_joker(joker_type);
}
