#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <chrono>

#include "properties.h"
#include "ball.h"
#include "object_initializations.h"
#include "block_generation.h"
#include "get_new_angle.h"
#include "score_logic.h"
#include "get_neighbours.h"
#include "lives_generation.h"
#include "text_animation.h"
#include "collision_handler.h"
#include "init_misc.h"
#include "drawing.h"


using namespace std::chrono;

//-------------------------------------------------------------------
int main()
{
    // Create the main window
    sf::RenderWindow main_window(sf::VideoMode(SCREENSIZE_X, SCREENSIZE_Y), "SFML window");

    sf::Event event;

    init_textures();

    //for random block generation
    std::srand(std::time(0));

    create_blocks_data();
    create_blocks_graphics();

    init_gamestate();
    assert(curr_gamestate.isInitialized);

    sf::CircleShape ball = init_ball();

    sf::RectangleShape plat = init_platform();

    sf::RectangleShape barrier = init_barrier();

    set_life_data();
    set_life_graphics();

    init_score();

    sf::RectangleShape status_bar = init_status_bar();

    sf::RectangleShape status_bar_logo = init_logo();

    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = high_resolution_clock::now();
	// Start the game loop
    while (main_window.isOpen() && game_active)
    {

        std::chrono::time_point<std::chrono::high_resolution_clock> curTtime = high_resolution_clock::now();
        std::chrono::milliseconds timePassed = duration_cast<milliseconds>(curTtime - lastTime);


        if(game_status == GAME_ACTIVE)
        {
            while (main_window.pollEvent(event))
            {
                // Close window : exit
                if (event.type == sf::Event::Closed)
                {
                    main_window.close();
                }

                else if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::A)
                    {
                        if(curr_gamestate.platform.x - curr_gamestate.platform.plat_speed > left_wall)
                        {
                            curr_gamestate.platform.x -= curr_gamestate.platform.plat_speed;
                        }
                        else
                        {
                            curr_gamestate.platform.x = left_wall;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::D)
                    {
                        if (curr_gamestate.platform.x + curr_gamestate.platform.width + curr_gamestate.platform.plat_speed < right_wall)
                        {
                            curr_gamestate.platform.x += curr_gamestate.platform.plat_speed;
                        }
                        else
                        {
                            curr_gamestate.platform.x = right_wall - curr_gamestate.platform.width;
                        }
                    }
                }
            }


            // ---------------------------------
            // CORE GAME LOOP FROM HERE
            // ---------------------------------
            if (alpha_y == 0 && alpha_x == 0)
            {
                // default movement at the start of the game
                curr_gamestate.ball.curr_x += get_new_x(curr_degrees);
                curr_gamestate.ball.curr_y += get_new_y(curr_degrees);
            }
            else
            {
                // all other movement
                curr_gamestate.ball.curr_x += alpha_x;
                curr_gamestate.ball.curr_y += alpha_y;
            }


            // MAIN COLLISIONS
            handle_collision_walls();
            handle_collision_block();
            handle_collision_platform();
            handle_collision_barrier();

            ball.setPosition(curr_gamestate.ball.curr_x, curr_gamestate.ball.curr_y);
            plat.setPosition(curr_gamestate.platform.x, curr_gamestate.platform.y);
            barrier.setPosition(barrier_obj.x, barrier_obj.y);

            check_gamestate();

        }
        else if(game_status == HEART_DEDUCTION)
        {

            TextAnimation(lastTime, curTtime, timePassed);
            DrawHeartDeductionText(main_window);
            while (main_window.pollEvent(event))
            {

                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        game_status = GAME_ACTIVE;
                        curr_degrees = BALL_STARTER_DEG;
                        curr_gamestate.ball.curr_x = BALL_START_POSX;
                        curr_gamestate.ball.curr_y = BALL_START_POSY;
                        handle_collision(COLLISION_CASE_RESET);
                        curr_gamestate.platform.x = curr_gamestate.platform.platform_starter_x;
                    }
                }
            }
        }
        else if(game_status == HEARTS_GONE)
        {
            TextAnimation(lastTime, curTtime, timePassed);
            DrawNoHeartsText(main_window);
            while (main_window.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    game_active = false;
                }
            }
        }
        else
        {
            DrawGameWonText(main_window);
            while (main_window.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    game_active = false;
                }
            }
        }

        DrawBlocks(main_window);
        DrawPlat(main_window, plat);
        DrawBarrier(main_window, barrier);
        DrawBall(main_window, ball);
        DrawStatusBar(main_window, status_bar);
        DrawStatusBarLogo(main_window, status_bar_logo);
        DrawScore(main_window);
        DrawHearts(main_window);

        main_window.display();

        // Clear screen
        main_window.clear();

    }

    return EXIT_SUCCESS;
}
