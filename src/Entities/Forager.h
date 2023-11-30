//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_FORAGER_H
#define LAB3_FORAGER_H

#include "Entity.h"

namespace EntityNS {
    /*!
     * @brief Класс Фуражира. Наследуется от Entity.
     */
    class Forager : public Entity {
    public:
        /*!
         * Конструктор фуражира. Изначально инвентарь пуст.
         * @param name название юнита
         */
        explicit Forager(const std::string &name);

        /*!
         * @brief Сбросить все предметы из инвентаря фуражира в inventory.
         * @param inventory - инвентарь для сброса.
         */
        void drop_all(InventoryNS::Inventory &inventory);

        // index in unit inventory
        /*!
         * @brief Сбросить предмет Фуражира в другой инвентарь.
         * @param inventory инвентарь для сброса.
         * @param index индекс предмета в инвентаре Фуражира, который нужно переложить.
         * @throws std::out_of_range - index not in [0, Inventory_.size())
         */
        void drop_into(InventoryNS::Inventory &inventory, int index);

        /*!
         * @brief Переложить предмет под index из inventory в инвентарь Фуражира.
         * @param inventory откуда взять предмет
         * @param index индекс предмета, который нужно взять из inventory.
         * @throws std::out_of_range - index not in [0, inventory.size())
         */
        void take_item(InventoryNS::Inventory &inventory, int index);

        /*!
         * @brief Выбросить предмет под index'ом из инвентаря Фуражира
         * @param index индекс предмета, который нужно сбросить
         * @return указатель на сброшенный предмет
         * @throws index not in [0, Inventory_.size())
         */
        std::unique_ptr<ItemNS::Item> throw_item(int index);

        [[nodiscard]] EntityType getType() const override;

        /*!
         *
         * @param new_i новая координата
         * @param new_j новая координата
         * @throws std::runtime_error - если не хватает очков действия
         * @throws std::invalid_argument шаг более, чем на одну клетку.
         */
        void move(int new_i, int new_j) override;

        /*!
         * @throws std::runtime_error, если персонаж еще жив.
         * @return инвентарь персонажа.
         */
        std::optional<InventoryNS::Inventory> die() override;

        /*!
         * Перемещает инвентарь.
         * @param invetnory - инвентраь, которым нужно инициализировать инвентарь Фуражира.
         */
        void setInvetnory(InventoryNS::Inventory &&invetnory);

    private:
        InventoryNS::Inventory Inventory_;
    };
}

#endif //LAB3_FORAGER_H
