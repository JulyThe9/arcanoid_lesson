#include <SFML/Graphics.hpp>


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    float posX = 50;
    float posY = 50;
    shape.setPosition(posX, posY);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::W)
                {
                    posY-=20;
                }
                else if(event.key.code == sf::Keyboard::A)
                {
                    posX-=20;
                }
                else if(event.key.code == sf::Keyboard::S)
                {
                     posY+=20;
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                     posX+=20;
                }
            }
        }
        // Clear screen
        app.clear();


        // Update position
        shape.setPosition(posX, posY);
        // Draw circle
        app.draw(shape);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
