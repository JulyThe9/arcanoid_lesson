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

//-------------------------------------------------------------------
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(screensizeX, screensizeY), "SFML window");

    sf::CircleShape ball = init_ball();

    sf::RectangleShape plat = init_platform();

    sf::RectangleShape block = init_block();

	// Start the game loop
cout << "left_bside: " << left_bside << endl;
cout << "top_bside: " << top_bside << endl;
cout << "bottom_bside: " << bottom_bside << endl;
cout << "right_bside: " << right_bside << endl;
cout << "block_width: " << block_width << endl;
cout << "block_len: " << block_len << endl;

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
            ballX += get_new_x(curr_degrees);
            ballY += get_new_y(curr_degrees);
        }
        else
        {
            // all other movement
            //cout << "alpha_x: " << alpha_x << "; alpha_y: " << alpha_y << endl;
            ballX += alpha_x;
            ballY += alpha_y;
        }

        temp_y = ballY;
        temp_x = ballX;


        // ---------------------------------
        // WALL COLLISION DETECTION HERE
        // ---------------------------------
        if(temp_y >= bottom_wall - ball_size * 2)
        {
            //cout << "======= Collision detected bottom wall! ========" << endl;
            //cout << ">temp_x: " << temp_x << "; temp_y: " << temp_y << endl;
            handle_collision('b');
        }
        else if(temp_x >= right_wall - ball_size * 2)
        {
            //cout << "======= Collision detected right wall! ========" << endl;
            //cout << ">temp_x: " << temp_x << "; temp_y: " << temp_y << endl;
            handle_collision('r');
        }
        else if(temp_y <= top_wall)
        {
            //cout << "======= Collision detected top wall! ========" << endl;
            //cout << ">temp_x: " << temp_x << "; temp_y: " << temp_y << endl;
            handle_collision('t');
        }
        else if(temp_x <= left_wall)
        {
            //cout << "======= Collision detected left wall! ========" << endl;
            //cout << ">temp_x: " << temp_x << "; temp_y: " << temp_y << endl;
            //cout << "left wall + ball size: " << left_wall + ball_size << endl;
            handle_collision('l');
        }
        else if(temp_y + ball_size >= platY - plat_len && temp_y + ball_size < platY + 0.01)

        {
            if(temp_x + ball_size * 2 >= platX && temp_x + ball_size <= platX + plat_width)
            {
                cout << "PLAT temp_x: " << temp_x << " temp_y: " << temp_y << endl;
                handle_collision('b');
            }
        }
        else if(temp_y + ball_size * 2 >= top_bside && temp_y < top_bside + 0.1)
        {
            if(temp_x > blockX && temp_x < blockX + block_width)
            {
                cout << "TOP temp_x: " << temp_x << " temp_y: " << temp_y << endl;
                handle_collision('b');
            }
        }
        else if(temp_x + ball_size * 2 >= left_bside && temp_x < left_bside + 0.1)
        {
            if(temp_y > top_bside && temp_y < bottom_bside)
            {
                cout << "LEFT temp_x: " << temp_x << " temp_y: " << temp_y << endl;
                handle_collision('l');
            }
        }
        else if(temp_y <= bottom_bside && temp_y > bottom_bside - 0.1)
        {
            if(temp_x > left_bside + ball_size && temp_x < right_bside)
            {
                cout << "BOTTOM temp_x: " << temp_x << " temp_y: " << temp_y << endl;
                handle_collision('t');
            }
        }
        else if(temp_x <= right_bside && temp_x > right_bside - 0.1)
        {
            if(temp_y >= top_bside && temp_y <= bottom_bside)
            {
                ball_speed = 0;
                cout << "RIGHT temp_x: " << temp_x << " temp_y: " << temp_y << endl;
                handle_collision('r');
            }
        }

        //cout << "PosX: " << ballX << "; PosY: " << ballY << endl;
        //cout << "AlpX: " << alpha_x << "; AlpY: " << alpha_y << endl;

        ball.setPosition(ballX, ballY);
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

