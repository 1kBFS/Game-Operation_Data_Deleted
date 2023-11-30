//
// Created by Pavel on 28.11.2023.
//

#ifndef LAB3_GAME_CONTROLLER_H
#define LAB3_GAME_CONTROLLER_H
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Tile_Map.h"
#include "../Game/Game.h"

namespace UI {
    class GameController {
    public:

        GameController(const std::string &config_filename, std::shared_ptr<tgui::Gui> ptr_gui);

        void move_handler(GameNS::Game::MoveDirectionType moveDirection);

        void to_view(sf::RenderWindow &window);
        bool isHandling() const;
    private:
        void update_unit_sprite();
        void update_visible_cells_sprite();
        static void change_unit_texture(const EntityNS::EntityType &newEntityType, sf::Sprite &sprite);
        void error_box(const std::string& msg);

        sf::Sprite ActiveUnitSprite_;
        TileMap Board_;
        GameNS::Game Game_;
        sf::Texture SpriteTexture_;
        std::shared_ptr<tgui::Gui> ptrGUI_;
        double ScaleX_ = 1;
        double ScaleY = 1;
        bool AnyWarning = false;

    };
}


#endif //LAB3_GAME_CONTROLLER_H
