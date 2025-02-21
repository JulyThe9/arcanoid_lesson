void add_to_score(int row, int col)
{
    int score_numberInt = stoi(curr_gamestate.score_number);
    block_type curr_block = curr_gamestate.blocks[row][col];
    score_numberInt += curr_block.block_value;
    curr_gamestate.score_number = to_string(score_numberInt);
    score.setString(curr_gamestate.score_number);
}
