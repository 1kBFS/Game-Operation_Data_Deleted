#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/UI/Game_Controller.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using namespace UI;
using namespace GameNS;

int main() {
    try {
        sf::RenderWindow window(sf::VideoMode(900, 800), "[~~Data Deleted~~]", sf::Style::Close);
        auto ptr_gui = std::make_shared<tgui::Gui>(window);
        GameController gameController("../files/configs/default.json", ptr_gui);
        sf::Texture layout_texture;
        if (!layout_texture.loadFromFile("../files/models/parchmentAncient.png")) {
            std::cerr << "Unable to load bg texture";
            return 0;
        }
        sf::Sprite layout(layout_texture);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ptr_gui->handleEvent(event);
                if (event.type == sf::Event::Closed)
                    window.close();
                if (gameController.isHandling()) {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::E) {
                            if (!gameController.isInventoryOpen()) {
                                gameController.show_inventory(UI::GameController::PERSON);
                            } else {
                                gameController.close_inventory();
                            }
                        } else if (event.key.code == sf::Keyboard::G) {
                            if (!gameController.isInventoryOpen()) {
                                gameController.show_inventory(UI::GameController::GROUND);
                            } else {
                                gameController.close_inventory();
                            }
                        } else if (event.key.code == sf::Keyboard::C) {
                            if (!gameController.isInventoryOpen()) {
                                gameController.show_inventory(UI::GameController::CONTAINER);
                            } else {
                                gameController.close_inventory();
                            }
                        } else if (gameController.isInventoryOpen()) {
                            gameController.message_box("You are in inventory mode. Close it before.");
                        } else {
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
                            if (event.key.code == sf::Keyboard::Left) {
                                gameController.change_player_handler(false);
                            }
                            if (event.key.code == sf::Keyboard::Right) {
                                gameController.change_player_handler();
                            }
                        }

                    }
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            auto pos = sf::Mouse::getPosition(window);
                            gameController.attack_handler(pos.x, pos.y);
                            std::cout << pos.x << " " << pos.y << "\n";
                        }
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            auto pos = sf::Mouse::getPosition(window);
                            gameController.enemy_info_handler(pos.x, pos.y);
                        }

                    }
                }

            }
            window.clear();
            window.draw(layout);
            gameController.to_view(window);
            window.display();
        }

    } catch (std::runtime_error& ex){
        std::cerr << ex.what() << "\n";
        return 0;
    }
}

