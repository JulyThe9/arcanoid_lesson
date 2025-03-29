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
#include "fu_ball.h"
#include "fu_platform.h"
#include "blocks.h"
#include "block_generation.h"
#include "barriar.h"
#include "get_new_angle.h"
#include "fu_score_logic.h"
#include "get_neighbours.h"
#include "heart.h"
#include "lives_generation.h"
#include "text_animation.h"
#include "fu_collision_handler.h"
#include "fu_init_misc.h"
#include "status_bar.h"
#include "logo.h"
#include "drawing.h"


using namespace std::chrono;

//-------------------------------------------------------------------
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

    sf::CircleShape ball = init_ball();

    sf::RectangleShape plat = init_platform();

    sf::RectangleShape barrier = init_barrier();

    init_textures();

    //for random block generation
    std::srand(std::time(0));

    create_blocks_data();
    create_blocks_graphics();

    set_life_data();
    set_life_graphics();

    init_score();

    sf::RectangleShape status_bar = init_status_bar();

    sf::RectangleShape status_bar_logo = init_logo();

    auto lastTime = high_resolution_clock::now();
	// Start the game loop
    while (app.isOpen() && game_active)
    {

        auto curTtime = high_resolution_clock::now();
        auto timePassed = duration_cast<milliseconds>(curTtime - lastTime);


        if(game_status == GAME_ACTIVE)
        {
            while (app.pollEvent(event))
            {
                // Close window : exit
                if (event.type == sf::Event::Closed)
                {
                    app.close();
                }

                else if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::A)
                    {
                        if(platX - curr_gamestate.plat_speed > left_wall)
                        {
                            platX -= curr_gamestate.plat_speed;
                        }
                        else
                        {
                            platX = left_wall;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::D)
                    {
                        if (platX + curr_gamestate.plat_width + curr_gamestate.plat_speed < right_wall)
                        {
                            platX += curr_gamestate.plat_speed;
                        }
                        else
                        {
                            platX = right_wall - curr_gamestate.plat_width;
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
                recent_posX += get_new_x(curr_degrees);
                recent_posY += get_new_y(curr_degrees);
                //TODO needs to be debugged
            }
            else
            {
                // all other movement
                recent_posX += alpha_x;
                recent_posY += alpha_y;
            }

            temp_y = recent_posY;
            temp_x = recent_posX;


            // MAIN COLLISIONS
            handle_collision_walls();
            handle_collision_block();
            handle_collision_platform();
            handle_collision_barrier();


            ball.setPosition(recent_posX, recent_posY);
            plat.setPosition(platX, platY);
            barrier.setPosition(barrierX, barrierY);

            check_gamestate();

        }
        else if(game_status == HEART_DEDUCTION)
        {

            TextAnimation(lastTime, curTtime, timePassed);
            DrawHeartDeductionText(app);
            while (app.pollEvent(event))
            {

                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        game_status = GAME_ACTIVE;
                        curr_degrees = ball_starter_deg;
                        recent_posX = ball_start_posX;
                        recent_posY = ball_start_posY;
                        handle_collision(COLLISION_CASE_RESET);
                        platX = platform_starter_X;
                    }
                }
            }
        }
        else if(game_status == HEARTS_GONE)
        {
            TextAnimation(lastTime, curTtime, timePassed);
            DrawNoHeartsText(app);
            while (app.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    game_active = false;
                }
            }
        }
        else
        {
            DrawGameWonText(app);
            while (app.pollEvent(event))
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    game_active = false;
                }
            }
        }

        if(temp_x == recent_posX)
        {
            cout << "WE ARE THE SAME" << endl;
        }

        DrawBlocks(app);
        DrawPlat(app, plat);
        DrawBarrier(app, barrier);
        DrawBall(app, ball);
        DrawStatusBar(app, status_bar);
        DrawStatusBarLogo(app, status_bar_logo);
        DrawScore(app);
        DrawHearts(app);

        app.display();


        // Clear screen
        app.clear();



    }

    return EXIT_SUCCESS;
}
