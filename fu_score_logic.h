void add_to_score(int block_number)
{
    int score_numberInt = stoi(gs.score_number);
    block_type curr_block = vector_data_block[block_number];
    score_numberInt += curr_block.block_value;
    gs.score_number = to_string(score_numberInt);
    score.setString(gs.score_number);
}
