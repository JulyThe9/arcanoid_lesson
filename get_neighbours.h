//curr_gamestate.blocks[candidate_block_row][candidate_block_col].active == true


bool is_valid_neighbour(int candidate_block_row, int candidate_block_col)
{
    if(candidate_block_row < block_rows &&
       candidate_block_row >= 0 &&
       candidate_block_col < block_columns &&
       candidate_block_col >= 0)
    {
        if(curr_gamestate.blocks[candidate_block_row][candidate_block_col].active)
        {
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> get_neighbours(int row, int col)
{
    bool valid;
    vector<pair<int, int>> block_neighbours;

    int upper_row = row - 1;
    int upper_col = col;
    valid = is_valid_neighbour(upper_row, upper_col);
    if(valid)
    {
        block_neighbours.push_back({upper_row, upper_col});

    }

    int right_row = row;
    int right_col = col + 1;
    valid = is_valid_neighbour(right_row, right_col);
    if(valid)
    {
        block_neighbours.push_back({right_row, right_col});
    }

    int lower_row = row + 1;
    int lower_col = col;
    valid = is_valid_neighbour(lower_row, lower_col);
    if(valid)
    {
        block_neighbours.push_back({lower_row, lower_col});

    }

    int left_row = row;
    int left_col = col - 1;
    valid = is_valid_neighbour(left_row, left_col);
    if(valid)
    {
        block_neighbours.push_back({left_row, left_col});

    }

    if(curr_gamestate.blocks[row][col].radius)
    {
        int upper_right_row = row - 1;
        int upper_right_col = col + 1;
        valid = is_valid_neighbour(upper_right_row, upper_right_col);
        if(valid)
        {
            block_neighbours.push_back({upper_right_row, upper_right_col});
        }

        int lower_bottom_row = row + 1;
        int lower_bottom_col = col + 1;
        valid = is_valid_neighbour(lower_bottom_row, lower_bottom_col);
        if(valid)
        {
            block_neighbours.push_back({lower_bottom_row, lower_bottom_col});
        }

        int lower_left_row = row + 1;
        int lower_left_col = col - 1;
        valid = is_valid_neighbour(lower_left_row, lower_left_col);
        if(valid)
        {
            block_neighbours.push_back({lower_left_row, lower_left_col});
        }

        int upper_left_row = row - 1;
        int upper_left_col = col - 1;
        valid = is_valid_neighbour(upper_left_row, upper_left_col);
        if(valid)
        {
            block_neighbours.push_back({upper_left_row, upper_left_col});
        }

        int upper_upper_row = row - 2;
        int upper_upper_col = col;
        valid = is_valid_neighbour(upper_upper_row, upper_upper_col);
        if(valid)
        {
            block_neighbours.push_back({upper_upper_row, upper_upper_col});

        }

        int right_right_row = row;
        int right_right_col = col + 2;
        valid = is_valid_neighbour(right_right_row, right_right_col);
        if(valid)
        {
            block_neighbours.push_back({right_right_row, right_right_col});
        }

        int lower_lower_row = row + 2;
        int lower_lower_col = col;
        valid = is_valid_neighbour(lower_lower_row, lower_lower_col);
        if(valid)
        {
            block_neighbours.push_back({lower_lower_row, lower_lower_col});

        }

        int left_left_row = row;
        int left_left_col = col - 2;
        valid = is_valid_neighbour(left_left_row, left_left_col);
        if(valid)
        {
            block_neighbours.push_back({left_left_row, left_left_col});
        }


    }
    return block_neighbours;
}
