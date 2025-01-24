void add_to_score(int block_number)
{
    int score_numberInt = stoi(score_number);
    block_type curr_block = vector_data_block[block_number];
    score_numberInt += curr_block.block_value;
    score_number = to_string(score_numberInt);
    score.setString(score_number);
}
