//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_LEVEL_H
#define LAB3_LEVEL_H

#include <vector>
#include <memory>
#include "Team.h"
#include "Cell.h"
#include "../Entities/Entity.h"
#include <functional>

namespace LevelNS {

    class Level {
    public:

        /*!
         * @brief Поместить юнит на поле.
         * @param new_pos куда помесиить юнит.
         * @param entity юнит для перемещения.
         * @throws std::out_of_range неправильные координаты.
         * @details Не тратит очки перемещения персонажа. Использовать для начального размещения юнитов на карте.
         */
        void place_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity);

        /*!
         * @brief Переместить юнит на поле.
         * @param new_pos куда переместить.
         * @param entity юнит для перемещния
         * @details Тратит очки перемещения.
         * @throws std::out_of_range неправильные координаты.
         */
        void move_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity);

        /*!
         * @brief Удалить юнит с поля.
         * @param entity юнит, который надо удалить с поля
         * @throws std::runtime_error если такого юнита на поле нет
         * @throws std::out_of_range неправильные координаты.
        */
        void remove_unit(std::shared_ptr<EntityNS::Entity> &entity);

        /*!
         * @brief Поместить предмет на поле в заданную клетку на землю
         * @param pos позциию, куда поместить пердмет
         * @param new_item предмет для размещения
         * @throws std::out_of_range неправильные координаты.
         */
        void place_item_ground(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Поместить все предметы из инвенторя на поле в заданную клетку
         * @param pos позциию, куда поместить пердмет
         * @param inventory инвентраь, откуда брать предметы
         * @throws std::out_of_range неправильные координаты.
         */
        void place_all_items_ground(std::pair<int, int> pos, InventoryNS::Inventory &inventory);

        /*!
         * @brief Поместить предмет на поле в заданную клетку в контейнер
         * @param pos позциию, куда поместить пердмет
         * @param new_item предмет для размещения
         * @throws std::out_of_range неправильные координаты.
         */
        void place_item_container(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Поместить все предметы из инвенторя в контейнер в заданной клетке
         * @param pos позцию, куда поместить предмет
         * @param inventory инвентраь, откуда брать предметы
         * @throws std::out_of_range неправильные координаты.
         */
        void place_all_items_container(std::pair<int, int> pos, InventoryNS::Inventory &inventory);

        /*!
         * @brief удалить предмет с земли
         * @param pos клетка, из которой удалить предмет
         * @param index индекс предмета на земле
         * @throws std::out_of_range неправильные координаты.
         */
        void remove_item_ground(std::pair<int, int> pos, int index);

        /*!
         * @brief удалить предмет из контейнера
         * @param pos клетка, из которой удалить предмет
         * @param index индекс предмета в контейнере
         * @throws std::out_of_range неправильные координаты.
         */
        void remove_item_container(std::pair<int, int> pos, int index);

        /*!
         * Поднять предмет с клетки с земли.
         * @param pos клетка, из ккоторой поднять предмет
         * @param index индекс предмета на земле
         * @return указатель на предмет
         */
        std::unique_ptr<ItemNS::Item> take_item_ground(std::pair<int, int> pos, int index);

        /*!
         * Поднять предмет из контейнера
         * @param pos клетка, из которой поднять предмет
         * @param index индекс предмета в контейнере
         * @return указатель на предмет
         */
        std::unique_ptr<ItemNS::Item> take_item_container(std::pair<int, int> pos, int index);

        [[nodiscard]]  InventoryNS::Inventory *get_inventory_ground(std::pair<int, int> pos);

        [[nodiscard]]  InventoryNS::Inventory *get_inventory_container(std::pair<int, int> pos);

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_ground(std::pair<int, int> pos) const;

        [[nodiscard]] std::vector<const ItemNS::Item *> show_items_container(std::pair<int, int> pos) const;

        void setCellType(std::pair<int, int> pos, CellType type);

        [[nodiscard]] CellType getCellType(std::pair<int, int> pos) const;

        /*!
         * @brief Получить клетки, которые видны из данной точки.
         * @param start_pos клетка, откуда смотрим
         * @param radius радиус обзора
         * @return вектор пар точек на карте, которые видны из данной.
         */
        std::vector<std::pair<int, int>> getVisibleCells(std::pair<int, int> start_pos, int radius) const;

        /*!
         * @brief Строим линию между центрами клеток. Аппроксимируем линию клетками. Полученные клетки - клетки на прямой между точками.
         * @param start_pos начальная координата
         * @param end_pos конечная координата
         * @return координаты клеток на прямой между заданными точками.
         */
        static std::vector<std::pair<int, int>>
        getCellsOnLine(std::pair<int, int> start_pos, std::pair<int, int> end_pos);

        /*!
         * Проверить, удовлетворяют ли все клетки заданному условию.
         * @param cells - набор координат клеток.
         * @param checker - функция чекер
         * @return true - удолетворяет, false - иначе
         * @warning Скоро будет улучшена проверка граничных точек.
         */
        bool check_all(std::vector<std::pair<int, int>> &cells, const std::function<bool(const Cell &)> &checker) const;

        /*!
         * Найти врагов для данного юнита.
         * @param my_entity юнит, для которого ищем врагов
         * @param my_team текущая команда
         * @param visiably_cells клекти, которые видны персонажу
         * @return вектор указателей на врагов.
         */
        std::vector<std::shared_ptr<EntityNS::Entity>>
        find_enemy(std::shared_ptr<EntityNS::Entity> &my_entity, TeamNS::Team &my_team,
                   std::vector<std::pair<int, int>> &visiably_cells) const;

        /*!
         * @brief Найти клетки с контейнерами
         */
        std::vector<std::pair<int, int>> find_container() const;

        explicit Level(int size = 0);

    private:

        [[nodiscard]] bool check_coords(std::pair<int, int> pos) const;

        std::vector<std::vector<Cell>> Board_;
    };

} // LevelNS

#endif //LAB3_LEVEL_H
