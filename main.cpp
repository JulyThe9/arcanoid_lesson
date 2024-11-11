#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\properties.h>
//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\fu_ball.h>
//#include <C:\Users\Master.DESKTOP-8NQ0SCM\Documents\codeblox_projects\arcanoid_lesson\fu_platform.h>

#include "properties.h"
#include "fu_ball.h"
#include "fu_platform.h"
#include "blocks.h"
#include "fu_collision_handler.h"



//-------------------------------------------------------------------
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

    sf::CircleShape ball = init_ball();

    sf::RectangleShape plat = init_platform();

    mult_block();


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
                    if(platX - plat_speed > left_wall)
                    {
                        platX -= plat_speed;
                    }
                    else
                    {
                        platX = left_wall;
                    }
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                    if (platX + plat_width + plat_speed < right_wall)
                    {
                        platX += plat_speed;
                    }
                    else
                    {
                        platX = right_wall - plat_width;
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


        ball.setPosition(recent_posX, recent_posY);
        plat.setPosition(platX, platY);

        app.draw(block);
        app.draw(ball);
        app.draw(plat);


        app.display();

        // Clear screen
        app.clear();

    }

    return EXIT_SUCCESS;
}
