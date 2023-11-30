//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include "../Level/Team.h"
#include "../Level/Level.h"
#include <map>

namespace GameNS {
    class Game {
    public:
        enum MoveDirectionType {
            LEFT, RIGHT, UP, DOWN
        };

        Game(int size, std::vector<TeamNS::Team> &&teams);

        Game() = default;

        void reset_time();

        void next_player();

        void next_team();

        void move(std::pair<int, int> new_pos);

        void move_direction(MoveDirectionType &direction);

        void shot(std::pair<int, int> attack_pos, std::shared_ptr<EntityNS::Entity> &enemy);

        void reload(int index);

        void use_aid(int index);

        void change_weapon(int index);

        void take_item_ground(int index);

        void take_item_container(int index);

        void throw_item_ground(int index = 0);

        void throw_item_container(int index = 0);

        void throw_all_items_ground();

        void throw_item_container();

        std::vector<ItemNS::Item *> show_items_ground();

        std::vector<ItemNS::Item *> show_items_container();

        std::vector<ItemNS::Item *> show_items_player();

        std::vector<std::pair<int, int>> find_containers();

        std::vector<std::shared_ptr<EntityNS::Entity>> find_enemy(std::vector<std::pair<int, int>> &visiably_cells);

        [[nodiscard]] std::vector<std::pair<int, int>> getVisibleCells() const;

        [[nodiscard]] const EntityNS::EntityType getPlayerType() const;

        [[nodiscard]] LevelNS::CellType getCellType(std::pair<int, int> pos) const;

        void setCellType(std::pair<int, int> pos, LevelNS::CellType new_type);

        std::pair<int, int> getActivePlayerCoord() const;

    private:
        TeamNS::Team::TeamIterator ActivePlayer_;
        std::vector<TeamNS::Team>::iterator ActiveTeam_;
        LevelNS::Level CurrentLevel_;
        std::vector<TeamNS::Team> Teams_;

        std::map<std::weak_ptr<EntityNS::Entity>, TeamNS::Team &> which_team;

        void take_item(int index, InventoryNS::Inventory *inventory);

        void throw_item(InventoryNS::Inventory *inventory, int index = 0);

        void throw_all(InventoryNS::Inventory *inventory);

        static std::vector<ItemNS::Item *> show_items(InventoryNS::Inventory &inventory);
    };

} // GameNS

#endif //LAB3_GAME_H
