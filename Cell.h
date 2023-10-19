//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_CELL_H
#define LAB3_CELL_H
#include "Inventory.h"
#include "Entity.h"
namespace LevelNS {
    enum CellType{FLOOR, WALL, WINDOW, BARRIER, CONTAINER};
    class Cell {
    public:
        //TODO:
        void place_item_ground(std::unique_ptr<ItemNS::Item>);
        void place_item_container(std::unique_ptr<ItemNS::Item>);
        void remove_item_ground(int index);
        void remove_item_container(int index);

        void place_unit(std::unique_ptr<EntityNS::Entity>);
        void remove_unit(int index);
        virtual ~Cell() = default;
    private:
        CellType Type_;
        InventoryNS::Inventory ItemsGround_;
        InventoryNS::Inventory ItemsContainer_;
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // CellNS

#endif //LAB3_CELL_H
