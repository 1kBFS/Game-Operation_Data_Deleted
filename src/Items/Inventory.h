//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_INVENTORY_H
#define LAB3_INVENTORY_H

#include <memory>
#include <vector>
#include "Item.h"
// All Items are unique.
namespace InventoryNS {
    /*!
     * @brief Класс инвентаря с предметами. Содержит предметы и суммарный вес.
     *
     * @details Copy c-tor и copy assigment оператор удалены. Объекты класса можно только перемещать. Все предметы хранятся, как unique_ptr.
     */
    class Inventory {
    public:
        typedef std::vector<std::unique_ptr<ItemNS::Item>>::const_iterator const_InventoryIterator;
        typedef std::vector<std::unique_ptr<ItemNS::Item>>::iterator InventoryIterator;

        Inventory() = default;

        Inventory(const Inventory &) = delete;

        Inventory &operator=(const Inventory &) = delete;

        /*!
         * @brief Move c-tor.
         *
         * @details Перемещает элементы из одного инвентаря в другой. Обнуляет curWeight.
         */
        Inventory(Inventory &&) noexcept;

        /*!
         * @brief Move assigment operator.
         *
         * @details Перемещает элементы из одного контейнера в другой. Обнуляет curWeight.
         */
        Inventory &operator=(Inventory &&inventory) noexcept;

        /*!
         * Найти предмет в инвентаре по названию.
         * @param title название предмета
         * @return Итератор на позицию предмета.
         */
        InventoryIterator find(const std::string &title);

        /*!
         * Найти предмет в инвентаре по индексу.
         * @param index требуемый индекс
         * @return Итератор на позицию предмета.
         */
        InventoryIterator find(int index);

        /*!
         * Удалить предмет, уменьшает суммарный вес инвентаря.
         * @param pos - итератор на позицию элемента, который надо удалить
         *
         */
        void erase(InventoryIterator pos);

        /*!
         * @brief Перемещает переданный предмет в конец инвентаря. Увеличивает суммарный вес.
         * @param new_item - указаетель на предмет
         */
        void push_back(std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Перемещает все предметы данного в конец текущего. inventory становится пустым.
         * @param inventory - инвентарь, откуда брать предметы
         */
        void put_all(Inventory &inventory);

        /*!
         * @brief Выбросить предмет из инвентаря. Уменьшает вес.
         * @param pos итератор на позицию элемента, который необходимо выбросить.
         * @return указатель на выброшенный предмет.
         */
        std::unique_ptr<ItemNS::Item> throw_item(InventoryIterator pos);

        [[nodiscard]] const_InventoryIterator begin() const;

        [[nodiscard]] const_InventoryIterator end() const;

        InventoryIterator begin();

        InventoryIterator end();

        [[nodiscard]] int getCurWeight() const;

        [[nodiscard]] int getSize() const;

        /*!
         * Получить список предметов в инвентаре.
         * @return вектор не владеющих! raw-pointers.
         */
        [[nodiscard]] std::vector<const ItemNS::Item *> show_items() const;

    private:
        int curWeight = 0;
        std::vector<std::unique_ptr<ItemNS::Item>> Elements_;
    };

} // InventoryNS

#endif //LAB3_INVENTORY_H
