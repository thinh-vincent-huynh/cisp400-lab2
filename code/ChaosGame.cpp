// Partners: Martin + Vincent

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Instructions part
    sf::Text text;
    sf::Font font;
    font.loadFromFile("CreamyCoffeeDemo-MV1Vp.ttf");
    text.setFont(font);
    text.setString("Please pick 3 random points. Esc to exit program.");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    // Extra part
    sf::Color rainbowColors[] = {
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Magenta
    };

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */
        if (points.size() > 0)
        {
            // Generate more points
            for (int i = 0; i < 6969; ++i)
            {
                // Select random vertex
                int rnd_point = rand() % 3; // Randomly choose one of the three vertices 
                Vector2f midpoint((vertices[rnd_point].x + points.back().x) / 2, (vertices[rnd_point].y + points.back().y) / 2); // Calculate midpoint between random vertex and the last point in the vector
                points.push_back(midpoint); // Push back the newly generated coord.
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */

        window.clear(); 
        window.draw(text);
        for (size_t i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        // Draw points
        if (!points.empty()) { 
            // 4th point
            RectangleShape pointShape(Vector2f(10, 10));
            pointShape.setFillColor(Color::White);
            pointShape.setPosition(Vector2f(points[0].x, points[0].y));
            window.draw(pointShape);


            // Midpoint points
            for (size_t i = 1; i < points.size(); ++i) {
                RectangleShape pointShape(Vector2f(1, 1));
                int colorIndex = static_cast<int>(points[i].y) / 15 % 5;
                pointShape.setFillColor(rainbowColors[colorIndex]);
                pointShape.setPosition(Vector2f(points[i].x, points[i].y));
                window.draw(pointShape);
            }
        }
        window.display();
    }
}