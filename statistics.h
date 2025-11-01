void request_user_input(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 8 && !username.empty()) // 8 is backspace
        {
            username.pop_back();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) // ASCII printable
        {
            username += static_cast<char>(event.text.unicode);
        }

        username_text.setString(username);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
    {
        if (!username.empty())
            has_input_username = true;
    }
}


void save_stats_to_file(const sf::Event& event, auto game_start_time)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        auto game_end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(game_end_time - game_start_time).count();
        set_score_test = curr_gamestate.score_number;
        std::ofstream file("score_statistics.txt", std::ios::app);

        int seconds = elapsed_seconds % 60;
        int minutes = (elapsed_seconds - seconds) / 60;

        if (file.is_open())
        {
            if(!has_user_won)
                file << username << "; " << set_score_test << "; " << minutes << "m " << seconds << "s; loss" << std::endl;
            else
                file << username << "; " << set_score_test << "; " << minutes << "m " << seconds << "s; win" << std::endl;
            file.close();
        }

        game_active = false;
    }
}
