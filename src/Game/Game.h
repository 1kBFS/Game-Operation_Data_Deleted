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

        void next_player();

        void prev_player();

        bool next_team();

        void move_direction(MoveDirectionType &direction);

        void use(int index);

        void take_item_ground(int index);

        void take_item_container(int index);

        void throw_item_ground(int index = 0);

        void throw_item_container(int index = 0);

        void attack(std::shared_ptr<EntityNS::Entity> &enemy);

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_ground() const;

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_container() const;

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_player() const;

        std::vector<std::shared_ptr<EntityNS::Entity>>
        find_enemy(std::vector<std::pair<int, int>> &visiably_cells) const;

        [[nodiscard]] std::vector<std::pair<int, int>> getVisibleCells() const;

        [[nodiscard]] const EntityNS::EntityType getPlayerType() const;

        [[nodiscard]] LevelNS::CellType getCellType(std::pair<int, int> pos) const;

        [[nodiscard]] LevelNS::CellType getMyCell() const;

        void setCellType(std::pair<int, int> pos, LevelNS::CellType new_type);

        [[nodiscard]] std::pair<int, int> getActivePlayerCoord() const;

        [[nodiscard]] std::pair<int, int> getActivePlayerHealth() const;

        [[nodiscard]] std::pair<int, int> getActivePlayerTime() const;

        [[nodiscard]] std::string getActivePlayerDesc() const;

        [[nodiscard]] std::vector<const EntityNS::Entity *> getTeammates() const;

        bool isCellEmpty(std::pair<int, int> pos);

        std::pair<int, int> getLevelSize() const;

    private:
        TeamNS::Team::TeamIterator ActivePlayer_;
        std::vector<TeamNS::Team>::iterator ActiveTeam_;
        LevelNS::Level CurrentLevel_;
        std::vector<TeamNS::Team> Teams_;

        void take_item(int index, InventoryNS::Inventory *inventory);

        void throw_item(InventoryNS::Inventory *inventory, int index = 0);

        void throw_all(InventoryNS::Inventory *inventory);

        static std::vector<const ItemNS::Item *> show_items(const InventoryNS::Inventory &inventory);

        void move(std::pair<int, int> new_pos);

        void reload(int index);

        void use_aid(int index);

        void change_weapon(int index);

        void shot(std::pair<int, int> attack_pos, std::shared_ptr<EntityNS::Entity> &enemy);

        void reset_time();

        bool checkGameOver();

        friend class GameConfig;
    };

} // GameNS

#endif //LAB3_GAME_H
