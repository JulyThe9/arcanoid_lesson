/**
*@file score_logic.h
*@brief adds current block value to score in correct way

*@author [Johannes Waldeck]
*@date [01.05.2025]
*/


/**
*@brief adds block value to score if block is hit and also handles graphics(drawing called in main)

*@param row row of current block
*@param col column of current block
*/
void add_to_score(int row, int col)
{
    int score_numberInt = stoi(curr_gamestate.score_number);
    block_type curr_block = curr_gamestate.blocks[row][col];
    score_numberInt += curr_block.block_value;
    #ifdef DEBUG
            cout << "-------------NEW SCORE---------------" << endl;
            cout << "score_number: " << score_numberInt << endl;
    #endif
    curr_gamestate.score_number = to_string(score_numberInt);
    int num_len = 6 - curr_gamestate.score_number.size();
    string string_len (num_len, '0');
    score.setString(string_len + curr_gamestate.score_number);
}
