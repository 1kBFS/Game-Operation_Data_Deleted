//
// Created by Pavel on 28.11.2023.
//

#ifndef LAB3_GAME_CONTROLLER_H
#define LAB3_GAME_CONTROLLER_H

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <unordered_map>
#include "Tile_Map.h"
#include "../Game/Game.h"

namespace UI {
    class GameController {
    public:
        enum InventoryViewType {
            GROUND, CONTAINER, PERSON
        };

        GameController(const std::string &config_filename, std::shared_ptr<tgui::Gui> ptr_gui);

        void move_handler(GameNS::Game::MoveDirectionType moveDirection);

        void attack_handler(float mouse_x, float mouse_y);

        void enemy_info_handler(float mouse_x, float mouse_y);

        void change_player_handler(bool next = true);

        void to_view(sf::RenderWindow &window);

        bool isHandling() const;

        bool isInventoryOpen() const;

        void close_inventory();

        void show_inventory(InventoryViewType type);

        void message_box(const std::string &msg, const std::string &title = "WARNING");

    private:
        void update_visible_units_sprite();

        void update_visible_cells_sprite();

        static void change_unit_texture(const EntityNS::EntityType &newEntityType, sf::Sprite &sprite);

        void update_sprite(sf::Sprite &sprite, const EntityNS::EntityType &newEntityType, std::pair<int, int> new_pos);

        void remove_from_inventory_menu(UI::GameController::InventoryViewType type, int index, int flag = 1);

        void update_unit_info_block();

        void use_button_callback(int index);

        void next_round_button_callback();

        /*!
         *
         * @param data first - cur, second - max
         * @param text - text on progress bar
         * @param color - color of bar
         */
        static tgui::ProgressBar::Ptr
        create_progress_bar(std::pair<int, int> data, const std::string &text, tgui::Color color);

        sf::Sprite ActiveUnitSprite_;
        TileMap Board_;
        GameNS::Game Game_;
        sf::Texture SpriteTexture_;
        sf::Texture NextRoundButtonTexture_;
        std::vector<std::pair<sf::Sprite, std::shared_ptr<EntityNS::Entity>>> EnemySprite_;
        std::vector<sf::Sprite> TeamSprite_;
        std::shared_ptr<tgui::Gui> ptrGUI_;
        tgui::Widget::Ptr CurrentInventory_;
        tgui::Widget::Ptr CurrentUnitInfo_;
        double ScaleX_ = 1;
        double ScaleY = 1;
        bool AnyWarning = false;
        bool InventoryOpen = false;

    };
}


#endif //LAB3_GAME_CONTROLLER_H
