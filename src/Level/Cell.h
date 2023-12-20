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

    /*!
     * @brief Клетка на поле.
     * @details Характеризуется предметами в контейнере, предметами на земле и список юнитов на клетке.
     */
    class Cell {
    public:
        /*!
         * Конструктор клетки
         * @param type тип клетки. По умолчанию FLOOR.
         */
        explicit Cell(CellType type = FLOOR) : Type_(type) {}

        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::iterator CellEntitiesIterator;
        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::const_iterator const_CellEntitiesIterator;
        /*!
         * @brief Поместить предмет на землю
         * @param new_item предмет для перемещения.
         * @throws std::invalid_argument если предмет на земле в данном типе клетки разместить нельзя.
         */
        void place_item_ground(std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Поместить все предметы на землю
         * @param inventory откуда брать предметы для размещения
         * @throws std::invalid_argument если предмет на земле в данном типе клетки разместить нельзя.
         */
        void place_all_items_ground(InventoryNS::Inventory &inventory);

        /*!
         * @brief Поместить предмет в контейнер.
         * @param new_item предмет для перемещения.
         * @throws std::invalid_argument если клетка - не контейнер.
         */
        void place_item_container(std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Поместить все предметы в контейнер на клетке.
         * @param inventory откуда брать предметы для размещения
         * @throws std::invalid_argument если клетка - не контейнер.
         */
        void place_all_items_container(InventoryNS::Inventory &inventory);

        /*!
         * Удалить предмет с земли.
         * @param index индекс предмета, который нужно удалить
         * @throws std::out_of_range индекс предмета в инвентаре неверный.
         */
        void remove_item_ground(int index);

        /*!
         * Удалить предмет из контейнера.
         * @param index индекс предмета, который нужно удалить
         * @throws std::out_of_range индекс предмета в инвентаре неверный.
         */
        void remove_item_container(int index);

        /*!
         * Поднять предмет с земли.
         * @param index индекс предмета, который нужно поднять с земли.
         * @throws std::out_of_range индекс предмета в инвентаре неверный.
         * @return указатель на предмет.
         */
        std::unique_ptr<ItemNS::Item> take_item_ground(int index);

        /*!
         * Изъять предмет из контейнера.
         * @param index индекс предмета, который нужно изъять  из контейнера
         * @throws std::out_of_range индекс предмета в инвентаре неверный.
         * @return указатель на предмет.
         */
        std::unique_ptr<ItemNS::Item> take_item_container(int index);

        /*!
         * Получить список предметов для отображения на земле.
         * @return std::vector не владеющих raw-pointers.
         */
        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_ground() const;

        /*!
         * Получить список предметов для отображения в контейнере.
         * @return std::vector не владеющих raw-pointers.
         */
        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_container() const;

        /*!
         * @brief Разместить юнит этой клетке.
         * @param entity - юнит для размещения
         * @throws std::invalid_argument в случае, если на клетке нельзя разметить юнит
         */
        void place_unit(std::shared_ptr<EntityNS::Entity> &entity);

        /*!
         * @brief Удалить юнита с клетки.
         * @param pos итератор на позицию в std::vector юнитов
         */
        void remove_unit(CellEntitiesIterator pos);

        [[nodiscard]] InventoryNS::Inventory *get_inventory_ground();

        [[nodiscard]] InventoryNS::Inventory *get_inventory_container();

        /*!
         * Найти юнита на клетке.
         * @param entity_to_find - указатель на юнита, который нужно найти
         * @return Итератор на позцию в std::vector юнитов.
         */
        CellEntitiesIterator find_unit(std::shared_ptr<EntityNS::Entity> &entity_to_find);

        CellEntitiesIterator begin();

        CellEntitiesIterator end();

        [[nodiscard]] const_CellEntitiesIterator begin() const;

        [[nodiscard]] const_CellEntitiesIterator end() const;

        [[nodiscard]] CellType getType() const;

        void setType(CellType type);

        /*!
         * Является ли клетка просматриваемой.
         * @param cell - клетка для исследования
         * @return true - является.
         */
        static bool isVisiable(const Cell &cell) {
            return cell.Type_ == WINDOW || cell.Type_ == FLOOR || cell.Type_==CONTAINER;
        }
        static bool isEmpty(const Cell &cell) {
            return cell.Type_ == FLOOR;
        }

        /*!
         * Можно ли простреливать клетку?
         * @param cell - клетка для исследования
         * @return true - является.
         */
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
