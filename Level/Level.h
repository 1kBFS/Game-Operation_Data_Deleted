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

namespace LevelNS {

    class Level {
    public:
        explicit Level(int size);
        void place_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity>& entity);
        void move_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity>& entity);
        void remove_unit(std::shared_ptr<EntityNS::Entity>& entity);

        void place_item_ground(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item>&& new_item);
        void place_all_items_ground(std::pair<int, int> pos, InventoryNS::Inventory& inventory);
        void place_item_container(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item);
        void place_all_items_container(std::pair<int, int> pos, InventoryNS::Inventory& inventory);

        void remove_item_ground(std::pair<int, int> pos, int index);
        void remove_item_container(std::pair<int, int> pos, int index);

        std::unique_ptr<ItemNS::Item> take_item_ground(std::pair<int, int> pos, int index);
        std::unique_ptr<ItemNS::Item> take_item_container(std::pair<int, int> pos, int index);

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_ground(std::pair<int, int> pos) const;
        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_container(std::pair<int, int> pos) const;

        void setCellType(std::pair<int, int> pos, CellType type);
        // https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0#%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F_%D0%BD%D0%B0_Python3
        void findVisiably(int i, int j, int radius, std::vector<std::pair<int, int>>& result);
        std::vector<std::shared_ptr<EntityNS::Entity>> find_enemy(std::shared_ptr<EntityNS::Entity>& my_entity, TeamNS::Team& my_team);
        std::vector<std::pair<int, int>> find_container();

    private:

        [[nodiscard]] bool check_coords(std::pair<int, int> pos) const;
        std::vector<TeamNS::Team> Teams_;
        std::vector<std::vector<Cell>> Board_;
    };

} // LevelNS

#endif //LAB3_LEVEL_H
