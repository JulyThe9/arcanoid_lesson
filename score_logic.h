void add_to_score(int row, int col)
{
    int score_numberInt = stoi(curr_gamestate.score_number);
    block_type curr_block = curr_gamestate.blocks[row][col];
    score_numberInt += curr_block.block_value;
    curr_gamestate.score_number = to_string(score_numberInt);
    int num_len = 6 - curr_gamestate.score_number.size();
    string string_len (num_len, '0');
    score.setString(string_len + curr_gamestate.score_number);
}
