//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_CELL_H
#define LAB3_CELL_H
#include "../Items/Inventory.h"
#include "../Entities/Entity.h"
namespace LevelNS {
    enum CellType{FLOOR, WALL, WINDOW, BARRIER, CONTAINER};
    class Cell {
    public:
        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::iterator CellEntitiesIterator;
        void place_item_ground(std::unique_ptr<ItemNS::Item> &&new_item);
        void place_all_items_ground(InventoryNS::Inventory& inventory);
        void place_item_container(std::unique_ptr<ItemNS::Item> &&new_item);
        void place_all_items_container(InventoryNS::Inventory& inventory);

        void remove_item_ground(int index);
        void remove_item_container(int index);

        void place_unit(std::shared_ptr<EntityNS::Entity>& entity);
        void remove_unit(CellEntitiesIterator pos);
        CellEntitiesIterator find_unit(std::shared_ptr<EntityNS::Entity>& entity_to_find);

        CellEntitiesIterator begin();
        CellEntitiesIterator end();
    private:
        [[nodiscard]] bool can_be_placed() const;
        [[nodiscard]] static bool is_same_entities(const std::shared_ptr<EntityNS::Entity>&lhs, const std::shared_ptr<EntityNS::Entity>& rhs) ;
        CellType Type_;
        InventoryNS::Inventory ItemsGround_;
        InventoryNS::Inventory ItemsContainer_;
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // CellNS

#endif //LAB3_CELL_H
