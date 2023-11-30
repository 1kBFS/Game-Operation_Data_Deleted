//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_CELL_H
#define LAB3_CELL_H

#include "../Items/Inventory.h"
#include "../Entities/Entity.h"

namespace LevelNS {
    enum CellType {
        FLOOR, WALL, WINDOW, BARRIER, CONTAINER, FOG
    };

    class Cell {
    public:
        explicit Cell(CellType type = FLOOR) : Type_(type) {}

        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::iterator CellEntitiesIterator;

        void place_item_ground(std::unique_ptr<ItemNS::Item> &&new_item);

        void place_all_items_ground(InventoryNS::Inventory &inventory);

        void place_item_container(std::unique_ptr<ItemNS::Item> &&new_item);

        void place_all_items_container(InventoryNS::Inventory &inventory);

        void remove_item_ground(int index);

        void remove_item_container(int index);

        std::unique_ptr<ItemNS::Item> take_item_ground(int index);

        std::unique_ptr<ItemNS::Item> take_item_container(int index);

        [[nodiscard]] std::vector<ItemNS::Item *> show_items_ground();

        [[nodiscard]] std::vector<ItemNS::Item *> show_items_container();

        void place_unit(std::shared_ptr<EntityNS::Entity> &entity);

        void remove_unit(CellEntitiesIterator pos);

        InventoryNS::Inventory *get_inventory_ground();

        InventoryNS::Inventory *get_inventory_container();

        CellEntitiesIterator find_unit(std::shared_ptr<EntityNS::Entity> &entity_to_find);

        CellEntitiesIterator begin();

        CellEntitiesIterator end();

        [[nodiscard]] CellType getType() const;

        void setType(CellType type);

        static bool isVisiable(const Cell &cell) {
            return cell.Type_ == WINDOW || cell.Type_ == FLOOR;
        }

        static bool isFragile(const Cell &cell) {
            return cell.Type_ == WINDOW || cell.Type_ == FLOOR || cell.Type_ == BARRIER;
        }


    private:
        [[nodiscard]] bool can_be_placed() const;

        [[nodiscard]] static bool
        is_same_entities(const std::shared_ptr<EntityNS::Entity> &lhs, const std::shared_ptr<EntityNS::Entity> &rhs);

        CellType Type_;
        InventoryNS::Inventory ItemsGround_;
        InventoryNS::Inventory ItemsContainer_;
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // CellNS

#endif //LAB3_CELL_H
