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

        struct HealthBar : public sf::Drawable, public sf::Transformable {
            explicit HealthBar(std::pair<int, int> data, std::pair<double, double> scale, sf::Vector2f position,
                               sf::Color color = sf::Color::Red)
                    : Base_(
                    sf::RectangleShape(sf::Vector2f(24 * scale.first, 5 * scale.second))) {
                Base_.setFillColor(sf::Color::Black);
                Bound_ = sf::RectangleShape(
                        sf::Vector2f(((static_cast<double>(data.first) / data.second) * 24) * scale.first,
                                     5 * scale.second));
                Bound_.setFillColor(color);
                Base_.setPosition(position.x, position.y + 24 * scale.second);
                Bound_.setPosition(position.x, position.y + 24 * scale.second);
                std::cout << Bound_.getPosition().x << " " << Bound_.getPosition().y << "\n";
            };

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
                states.transform *= getTransform();
                target.draw(Base_, states);
                target.draw(Bound_, states);
            }

            sf::RectangleShape Bound_;
            sf::RectangleShape Base_;
        };

        std::vector<std::pair<sf::Sprite, std::shared_ptr<EntityNS::Entity>>> EnemySprite_;
        std::vector<HealthBar> EnemyHealthBarSprite_;

        std::vector<sf::Sprite> TeamSprite_;
        std::vector<HealthBar> TeamHealthBarSprite_;

        std::shared_ptr<tgui::Gui> ptrGUI_;
        tgui::Widget::Ptr CurrentInventory_;
        tgui::Widget::Ptr CurrentUnitInfo_;
        bool AnyWarning = false;
        bool InventoryOpen = false;
    protected:
        double ScaleX_ = 1;
        double ScaleY_ = 1;
    };
}


#endif //LAB3_GAME_CONTROLLER_H
