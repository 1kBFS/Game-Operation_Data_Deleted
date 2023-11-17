#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "[Deleted]");
    window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // --draw--
        window.draw(shape);
        window.display();
    }

}
