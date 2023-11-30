#include <iostream>
#include <SFML/Graphics.hpp>
#include "UI/Game_Controller.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using namespace UI;
using namespace GameNS;

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "[~~Data Deleted~~]", sf::Style::Close);
    auto ptr_gui = std::make_shared<tgui::Gui>(window);
    GameController gameController("hahah", ptr_gui);
    sf::Texture layout_texture;
    layout_texture.loadFromFile("../models/parchmentAncient.png");
    sf::Sprite layout(layout_texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ptr_gui->handleEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            if (gameController.isHandling()) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W) {
                        gameController.move_handler(GameNS::Game::UP);
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        gameController.move_handler(GameNS::Game::LEFT);
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        gameController.move_handler(GameNS::Game::DOWN);
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        gameController.move_handler(GameNS::Game::RIGHT);
                    }
                }
            }
        }
        window.clear();
        window.draw(layout);
        gameController.to_view(window);
        window.display();
    }

}
