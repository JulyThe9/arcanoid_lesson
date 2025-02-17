#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\properties.h>
//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\fu_ball.h>
//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\fu_platform.h>

#include "properties.h"
#include "fu_ball.h"
#include "fu_platform.h"
#include "blocks.h"
#include "block_generation.h"
#include "barriar.h"
#include "lives.h"
#include "lives_generation.h"
//#include "life_animation.h"
#include "get_new_angle.h"
#include "fu_score_logic.h"
#include "fu_collision_handler.h"
#include "fu_init_misc.h"




//-------------------------------------------------------------------
int main()
{
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



	// Start the game loop
    while (app.isOpen())
    {
        // ---------------------------------
        // BUTTONS ON APP (Process events)
        // ---------------------------------
        sf::Event event;
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
                    if(platX - gs.plat_speed > left_wall)
                    {
                        platX -= gs.plat_speed;
                    }
                    else
                    {
                        platX = left_wall;
                    }
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                    if (platX + gs.plat_width + gs.plat_speed < right_wall)
                    {
                        platX += gs.plat_speed;
                    }
                    else
                    {
                        platX = right_wall - gs.plat_width;
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


        //MAIN COLLISIONS
        handle_collision_walls();
        handle_collision_block();
        handle_collision_platform();
        handle_collision_barrier();


        ball.setPosition(recent_posX, recent_posY);
        plat.setPosition(platX, platY);
        barrier.setPosition(barrierX, barrierY);

        for (int i = 0; i < block_amount; i++)
        {
            app.draw(vector_graphics_block[i]);
        }

        for(int i = 0; i < lives_amount; i++)
        {
            app.draw(vector_graphics_life[i]);
        }

        app.draw(plat);
        app.draw(barrier);
        app.draw(ball);
        app.draw(score);

        app.display();

        // Clear screen
        app.clear();

    }

    return EXIT_SUCCESS;
}
