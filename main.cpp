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
//#include "fu_collision_handler.h"

//-------------------------------------------------------------------
int handle_collision_walls()
{
    if(temp_y >= bottom_wall - ball_size * 2)
        {
            handle_collision('b');
        }
        else if(temp_x >= right_wall - ball_size * 2)
        {
            handle_collision('r');
        }
        else if(temp_y <= top_wall)
        {
            handle_collision('t');
        }
        else if(temp_x <= left_wall)
        {
            handle_collision('l');
        }
    cout << "Arthurs" << endl;
}


// ---------------------------------
// PLATFORM COLLISION DETECTION HERE
// ---------------------------------
int handle_collision_platform()
{
    if(temp_y + ball_size * 2 >= top_bside && temp_y < top_bside + 0.1)
    {
        if(temp_x > blockX && temp_x < blockX + block_width)
        {
            handle_collision('b');
        }
    }
}


// ---------------------------------
// BLOCK COLLISION DETECTION HERE
// ---------------------------------
int handle_collision_block()
{
    if(temp_y + ball_size * 2 >= top_bside && temp_y < top_bside + 0.1)
    {
        if(temp_x > blockX && temp_x < blockX + block_width)
        {
            handle_collision('b');
        }
    }
    else if(temp_x + ball_size * 2 >= left_bside && temp_x < left_bside + 0.1)
    {
        if(temp_y > top_bside && temp_y < bottom_bside)
        {
            handle_collision('r');
        }
    }
    else if(temp_y <= bottom_bside && temp_y > bottom_bside - 0.1)
    {
        if(temp_x > left_bside + ball_size && temp_x < right_bside)
        {
            handle_collision('t');
        }
    }
    else if(temp_x <= right_bside && temp_x > right_bside - 0.1)
    {
        if(temp_y >= top_bside && temp_y <= bottom_bside)
        {
            handle_collision('l');
        }
    }
}
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

    sf::CircleShape ball = init_ball();

    sf::RectangleShape plat = init_platform();

    sf::RectangleShape block = init_block();

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
            //cout << "alpha_x: " << alpha_x << "; alpha_y: " << alpha_y << endl;
            recent_posX += alpha_x;
            recent_posY += alpha_y;
        }

        temp_y = recent_posY;
        temp_x = recent_posX;


        //MAIN COLLISIONS
        handle_collision_walls();
        cout << "1111111111" << endl;
        handle_collision_walls();
        cout << "2222222222" << endl;
        handle_collision_block();
        cout << "3333333333" << endl;


        ball.setPosition(recent_posX, recent_posY);
        plat.setPosition(platX, platY);

        app.draw(ball);
        app.draw(plat);
        app.draw(block);


        app.display();

        // Clear screen
        app.clear();

    }

    return EXIT_SUCCESS;
}
