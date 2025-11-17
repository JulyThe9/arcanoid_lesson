
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


void set_new_score(std::chrono::high_resolution_clock::time_point game_start_time)
{
    // win/loss status
    string status = "loss";
    if (has_user_won)
        status = "win";

    // Dreamlo private key used for score submission
    const string privateKey = "nzrw8nnnw0ONVdJJzqV_hgvsxxmMJfCUWQU25fEb69Aw";

    // Calculate how long the game took
    auto game_end_time = std::chrono::high_resolution_clock::now();

    // Convert time difference (duration) into seconds
    auto duration = game_end_time - game_start_time;

    // Convert duration into a plain integer (seconds)
    long elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

    // Convert seconds into a string (since URL needs text)
    string elapsed_seconds_str = to_string(elapsed_seconds);

    // Build the Dreamlo request URL
    // -----------------------------
    // Example:
    // http://dreamlo.com/lb/<privateKey>/add/<username>/<score>/<time>/<status>
    string url = "http://dreamlo.com/lb/" + privateKey +
                                        "/add/" + username +
                                        "/" + curr_gamestate.score_number +
                                        "/" + elapsed_seconds_str +
                                        "/" + status;

    // Init CURL
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // Convert C++ string into C-style string for curl
        const char* url_cstr = url.c_str();

        // Set the URL that curl will read from
        CURLcode set_url_result = curl_easy_setopt(curl, CURLOPT_URL, url_cstr);

        // Tell curl to automatically follow HTTP redirects
        long follow_location_flag = 1L;
        CURLcode set_follow_result = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, follow_location_flag);

        // -----------------------------
        // Actually perform the HTTP request
        // -----------------------------
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cerr << "Dreamlo upload failed: "
                      << curl_easy_strerror(res) << endl;   // curl_easy_strerror converts the error code into readable text
        }
        else
        {
            cout << "Score successfully uploaded!\n";
        }

        // Cleanup curl
        curl_easy_cleanup(curl);
    }
}


void save_stats_to_file(auto game_start_time)
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
            file << username << ";" << set_score_test << ";" << minutes << "m" << seconds << "s;" << "loss" << std::endl;
        else
            file << username << ";" << set_score_test << ";" << minutes << "m" << seconds << "s;" << "win" << std::endl;
        file.close();
    }

    game_active = false;

}
