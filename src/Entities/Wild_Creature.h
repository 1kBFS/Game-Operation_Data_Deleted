//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_WILD_CREATURE_H
#define LAB3_WILD_CREATURE_H
#include "Entity.h"
namespace EntityNS {
    /*!
     * @brief Класс дикого существа. Наследуется от Entity.
     */
    class WildCreature: public Entity {
    public:
        /*!
         * Конструктор для дикого существа.
         * @param name название юнита
         * @param damage урон в ближнем бою
         * @param accuracy точность(= вероятность попадания)
         */
        explicit WildCreature(const std::string &name, int damage=1, int accuracy=75);

        [[nodiscard]] EntityType getType() const override;
        /*!
         * Метод перемещения.
         * @param new_i новая координата
         * @param new_j новая координата
         * @throws std::runtime_error - если не хватает очков действия
         * @throws std::invalid_argument шаг более, чем на одну клетку.
         */
        void move(int new_i, int new_j) override;
        /*!
         *
         * @return  любом случае std::nullopt
         * @throws std::runtime_error в случае, если персонаж еще жив.
         */
        std::optional<InventoryNS::Inventory> die() override;
        /*!
         * Нанести урон. В любом случае отнимает 1 очко действия.
         * @param enemy - враг, по которому нужно нанести урон
         * @return true, в случае попадания, false в случае неудачи.
         * @throws std::invalid_argument враг не в клетки с персонажем
         * @throws std::runtime_error не хватает очков действия для совершения атаки
         */
        bool shot(EntityNS::Entity &enemy);

        ~WildCreature() override = default;

    private:
        int Damage_ = 1;
        int Accuracy_ = 75;
    };

} // EntityNS

#endif //LAB3_WILD_CREATURE_H
