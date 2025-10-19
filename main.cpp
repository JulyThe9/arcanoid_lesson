#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <chrono>
#include <fstream>

#include "properties.h"
#include "ball.h"
#include "object_initializations.h"
#include "block_generation.h"
#include "plat_movement.h"
#include "get_new_angle.h"
#include "score_logic.h"
#include "get_neighbours.h"
#include "lives_generation.h"
#include "sound.h"
#include "text_animation.h"
#include "powerups.h"
#include "timers.h"
#include "drawing.h"
#include "collision_handler.h"
#include "init_misc.h"


using namespace std::chrono;

//-------------------------------------------------------------------


int main()
{
    // Create the main window
    sf::RenderWindow main_window(sf::VideoMode(SCREENSIZE_X, SCREENSIZE_Y), "SFML window");
    main_window.setMouseCursorVisible(false);
    sf::Event event;

    init_textures();
    init_sounds();
    init_fonts();

    init_music();
    background_music.play();

    //for random block generation
    std::srand(std::time(0));

    create_blocks_data();
    create_blocks_graphics();

    init_gamestate();
    assert(curr_gamestate.isInitialized);

    ball = init_ball(curr_gamestate.ball);
    //sf::CircleShape dupe_ball = init_ball(curr_gamestate.dupe_ball);

    sf::RectangleShape predicting_plat = init_predicting_plat();

    barrier = init_barrier();

    set_life_data();
    set_life_graphics();

    init_score();

    status_bar = init_status_bar();

    status_bar_logo = init_logo();

    std::chrono::time_point<std::chrono::high_resolution_clock> predicting_plat_shown_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = high_resolution_clock::now();
    sf::Mouse::setPosition({curr_gamestate.platform.x, curr_gamestate.platform.y}, main_window); // window is a sf::Window




	// Start the game loop
    while (main_window.isOpen() && game_active)
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> curTtime = high_resolution_clock::now();
        std::chrono::milliseconds timePassed = duration_cast<milliseconds>(curTtime - lastTime);

        plat = init_platform();

        if(game_status == GAME_ACTIVE)
        {
            while (main_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    main_window.close();
                }
                plat_movement(main_window);
            }


            // ---------------------------------
            // CORE GAME LOOP FROM HERE
            // ---------------------------------
            if (curr_gamestate.ball.alpha_y == 0 && curr_gamestate.ball.alpha_x == 0)
            {
                // default movement at the start of the game
                curr_gamestate.ball.curr_x += get_new_x(curr_degrees, curr_gamestate.ball);
                curr_gamestate.ball.curr_y += get_new_y(curr_degrees, curr_gamestate.ball);
            }
            else
            {
                // all other movement
                curr_gamestate.ball.curr_x += curr_gamestate.ball.alpha_x;
                curr_gamestate.ball.curr_y += curr_gamestate.ball.alpha_y;
            }

            // MAIN COLLISIONS
            handle_collision_walls(curr_gamestate.ball);
            handle_collision_block(curr_gamestate.ball, curr_gamestate.blocks, curr_gamestate.blocks_graphics);
            //handle_collision_platform(main_window, curr_gamestate.ball, dupe_ball, curr_gamestate.blocks, curr_gamestate.blocks_graphics);
            handle_collision_platform(main_window, curr_gamestate.ball, curr_gamestate.blocks, curr_gamestate.blocks_graphics);
            handle_collision_barrier(curr_gamestate.ball, curr_gamestate.blocks);
            handle_collision_powerup();

            handle_deletion_powerup();

            ball.setPosition(curr_gamestate.ball.curr_x, curr_gamestate.ball.curr_y);
            plat.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);
            barrier.setPosition(barrier_obj.x, barrier_obj.y);


            if (is_trajectory_prediction_shown || in_blinking_animation == true)
            {
                // if timer not started yet, start it once
                if (predicting_plat_shown_time == std::chrono::time_point<std::chrono::high_resolution_clock>{})
                    predicting_plat_shown_time = std::chrono::high_resolution_clock::now();

                auto curTime = std::chrono::high_resolution_clock::now();
                auto platform_prediction_passed_time =
                    std::chrono::duration_cast<std::chrono::milliseconds>(curTime - predicting_plat_shown_time);

                predicting_plat.setPosition(predicting_x, predicting_y);
                if(is_trajectory_prediction_shown)
                    draw_predicting_plat(main_window, predicting_plat);

                platform_prediction_animation(platform_prediction_passed_time);

                if (platform_prediction_passed_time.count() > PLATFORM_PREDICTION_APPEARENCE_PERIOD)
                {
                    is_trajectory_prediction_shown = false;
                    predicting_plat_shown_time = {}; // reset timer
                    in_blinking_animation = false;
                }
            }
            else
            {
                // if prediction not shown, reset timer just in case
                predicting_plat_shown_time = {};
            }


            check_gamestate();

        }
        else if (game_status == HEART_DEDUCTION)
        {
            clean_up_timers();
            reset_powerups();
            static bool countdown_started = false;
            text_animation(lastTime, curTtime, timePassed);

            if(countdown_started)
            {
                user_status_text_visible = false;
                reset_platform(plat, main_window);
                reset_ball(ball);
            }
            if (user_status_text_visible)
                draw_heart_deduction_text(main_window);

            while (main_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    main_window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    if (!countdown_started)
                    {
                        countdown_active = true;
                        countdown_start_time = std::chrono::high_resolution_clock::now();
                        curr_countdown_num = COUNTDOWN_THREE;
                        set_countdown_three();
                        countdown_started = true;
                        play_countdown_sound();
                    }
                }
            }

            countdown_animation(curTtime);

            if (countdown_active)
            {
                if (curr_countdown_num == COUNTDOWN_THREE)
                    main_window.draw(countdown_three);
                else if (curr_countdown_num == COUNTDOWN_TWO)
                    main_window.draw(countdown_two);
                else if (curr_countdown_num == COUNTDOWN_ONE)
                    main_window.draw(countdown_one);
            }

            if (countdown_started && !countdown_active)
            {
                countdown_started = false;
                game_status = GAME_ACTIVE;
                handle_collision(COLLISION_CASE_RESET, curr_gamestate.ball);
                curr_gamestate.ball.last_collision = COLLISION_CASE_RESET;
            }
        }
        else if(game_status == HEARTS_GONE)
        {
            text_animation(lastTime, curTtime, timePassed);
            if(user_status_text_visible)
                draw_no_hearts_text(main_window);
            while (main_window.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {

                    game_active = false;
                }
            }
        }
        else if(game_status == BLOCKS_GONE)
        {
            clean_up_timers();
            text_animation(lastTime, curTtime, timePassed);
            if(user_status_text_visible)
                draw_game_won_text(main_window);
            while (main_window.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {

                    game_active = false;
                }
            }
        }


        //cout << "alpha x: " << curr_gamestate.ball.alpha_x << endl;
        //cout << "alpha y: " << curr_gamestate.ball.alpha_y << endl;
        // cout << "curr_pos_x: " << curr_gamestate.ball.curr_x << endl;
        // cout << "curr degrees: " << curr_degrees << endl;
        // cout << "-----------------" << endl;


        draw_everything(main_window);
        //dupe_ball.setPosition(curr_gamestate.dupe_ball.curr_x, curr_gamestate.dupe_ball.curr_y);
        //draw_ball(main_window, dupe_ball);

        main_window.display();

        // Clear screen
        main_window.clear();

        if (background_music.getStatus() != sf::Music::Playing)
        {
            background_music.play();
        }
    }

    return EXIT_SUCCESS;
}
