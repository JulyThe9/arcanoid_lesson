void play_wall_sound()
{
    sound_wall.setBuffer(buffer_wall);
    sound_wall.setVolume(10);
    sound_wall.play();
}


void init_music()
{
    background_music.setLoop(true);
    background_music.setPitch(1.0f);
    background_music.setVolume(0.0f);
}



void play_countdown_sound()
{
    sound_countdown.setBuffer(buffer_countdown);
    sound_countdown.setVolume(50);
    sound_countdown.play();
}


void play_game_continue_sound()
{
    sound_game_continue.setBuffer(buffer_game_continue);
    sound_game_continue.setVolume(20);
    sound_game_continue.play();
}
