//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_LEVEL_H
#define LAB3_LEVEL_H

#include <vector>
#include <memory>
#include "Team.h"
#include "../Game/Matrix.h"
#include "Cell.h"
#include "../Entities/Entity.h"
#include <functional>

namespace LevelNS {

    class Level {
    public:
        explicit Level(int size=0);

        void place_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity);

        void move_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity);

        void remove_unit(std::shared_ptr<EntityNS::Entity> &entity);

        void place_item_ground(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item);

        void place_all_items_ground(std::pair<int, int> pos, InventoryNS::Inventory &inventory);

        void place_item_container(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item);

        void place_all_items_container(std::pair<int, int> pos, InventoryNS::Inventory &inventory);

        void remove_item_ground(std::pair<int, int> pos, int index);

        void remove_item_container(std::pair<int, int> pos, int index);

        std::unique_ptr<ItemNS::Item> take_item_ground(std::pair<int, int> pos, int index);

        std::unique_ptr<ItemNS::Item> take_item_container(std::pair<int, int> pos, int index);

        InventoryNS::Inventory *get_inventory_ground(std::pair<int, int> pos);

        InventoryNS::Inventory *get_inventory_container(std::pair<int, int> pos);

        [[nodiscard]] std::vector<ItemNS::Item *> show_items_ground(std::pair<int, int> pos);

        [[nodiscard]] std::vector<ItemNS::Item *> show_items_container(std::pair<int, int> pos);

        void setCellType(std::pair<int, int> pos, CellType type);

        [[nodiscard]] CellType getCellType(std::pair<int, int> pos) const;

        std::vector<std::pair<int, int>> getVisibleCells(std::pair<int, int> start_pos, int radius) const;

        static std::vector<std::pair<int, int>>
        getCellsOnLine(std::pair<int, int> start_pos, std::pair<int, int> end_pos);

        bool check_all(std::vector<std::pair<int, int>> &cells, const std::function<bool(const Cell &)> &checker) const;

        std::vector<std::shared_ptr<EntityNS::Entity>>
        find_enemy(std::shared_ptr<EntityNS::Entity> &my_entity, TeamNS::Team &my_team,
                   std::vector<std::pair<int, int>> &visiably_cells);

        std::vector<std::pair<int, int>> find_container();

    private:

        [[nodiscard]] bool check_coords(std::pair<int, int> pos) const;

        std::vector<std::vector<Cell>> Board_;
    };

} // LevelNS

#endif //LAB3_LEVEL_H
