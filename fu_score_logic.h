void score_logic(int i)
{
    int score_numberInt = stoi(score_number);

    if (vector_data_block[i].texture_type == 0)
    {
        score_numberInt += 10;
    }
    else
    {
        score_numberInt += 20;
    }
    score_number = to_string(score_numberInt);
    score.setString(score_number);
}
