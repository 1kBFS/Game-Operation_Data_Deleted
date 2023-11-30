//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_INTELLIGENT_CREATURE_H
#define LAB3_INTELLIGENT_CREATURE_H

#include "Entity.h"
#include "../Items/Weapon.h"

namespace EntityNS {
    /*!
     * @brief Разумное существо. Наследуется от Entity.
     */
    class IntelligentCreature : public Entity {
    public:
        /*!
         * Конструктор для разумного существа.
         * @param name название юнита.
         * @param accuracy точность(= вероятность попадания)
         */
        explicit IntelligentCreature(const std::string &name, int accuracy = 75);

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
         * Метод смерти.
         * @throws std::runtime_error, если персонаж еще жив.
         * @return Если у юнита есть активное оружие, то создается инвентарь, его содержащий. Иначе std::nullopt.
         */
        std::optional<InventoryNS::Inventory> die() override;

        /**
        * \brief Выстрелить по врагу
        * \param enemy Ссылка на объект EntityNS::Entity, представляющий врага
        * \return true, если выстрел успешен, false, если нет
        * \throw std::runtime_error, если нет активного оружия или слишком мало времени для выполнения операции
        * \details Функция пытается выстрелить по врагу с помощью активного оружия, учитывая вероятность попадания и время выстрела.
        * Если выстрел успешен, то уменьшает здоровье врага на значение, возвращаемое функцией shot активного оружия.
        * Если выстрел неудачен, то ничего не делает. В любом случае уменьшает текущее время на значение, возвращаемое функцией getShotTime активного оружия.
        */
        bool shot(EntityNS::Entity &enemy);

        /*!
         * Выбросить активное оружие.
         * @return указатель на выброшенное оружие.
         * @throws std::runtime_error если нет активного оружия
         */
        std::unique_ptr<ItemNS::Item> throw_weapon();

        /*!
         * Перемещает оружие в слот активного оружия юнита.
         * @param new_item - новое оружие
         * @throws std::runtime_error если у юнита уже есть активное оружие.
         */
        void put_weapon(std::unique_ptr<WeaponNS::Weapon> &&new_item);

        /*!
         * Взять оружие из инвентаря. Перемещает оружие в слот активного оружия юнита.
         * @param inventory откуда брать оружие
         * @param index - индекс предмета в инвентаре
         * @throws std::runtime_error у юнита уже есть оружие
         * @throws std::out_of_range неверный индекс
         * @throws std::invalid_argument по индексом лежит не оружие
         */
        void take_item(InventoryNS::Inventory &inventory, int index);

    private:
        int Accuracy_;
        std::unique_ptr<WeaponNS::Weapon> ActiveWeapon_;
    };

} // EntityNS

#endif //LAB3_INTELLIGENT_CREATURE_H
