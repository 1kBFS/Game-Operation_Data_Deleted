//
// Created by Master on 17.10.2023.
//

#ifndef LAB3_OPERATIVE_H
#define LAB3_OPERATIVE_H

#include <memory>
#include <optional>

#include "Entity.h"
#include "../Items/Inventory.h"
#include "../Items/Weapon.h"

namespace EntityNS {
    /*!
     * @brief Класс оперативника. Наследуется от Entity.
     */
    class Operative : public EntityNS::Entity {
    public:

        /*!
         * Конструктор оперативника.
         * @param name название юнита
         * @param maxHeatPoint максимальное кол-во очков здоовья
         * @param curHeatPoint текущее кол-во очков здоровья.
         * @param curTime текущее кол-во очков действия
         * @param avaliableTime максимальное кол-во очков действия на раунд
         * @param stepTime кол-во чоков действия на шаг
         * @param visibilityRadius радиус обзора
         * @param reloadTime кол-во очков действия на перезарядку
         * @param maxWeight максимальный носимый вес
         * @param accuracy точность(= вероятность попадания)
         */
        explicit Operative(const std::string &name, int maxHeatPoint = 100, int curHeatPoint = 100, int curTime = 100,
                           int avaliableTime = 100, int stepTime = 1,
                           int visibilityRadius = 3, int reloadTime = 2, int maxWeight = 15, int accuracy = 100);

        /*!
         * Сменить активное оружие. Старое оружие, при его наличии, уходит в инвентарь.
         * @param index индекс предмета инвентаря, под которым лежит новое активное оружие.
         * @throws std::out_of_range неверный index предмета в инвентаре
         * @throws std::invalid_argument нет оружия под заданным индексом
         */
        void change_weapon(int index);

        /*!
         * @brief Переложить предмет под index из inventory в инвентарь Оперативника.
         * @param inventory откуда взять предмет
         * @param index индекс предмета, который нужно взять из inventory.
         * @throws std::out_of_range - index not in [0, inventory.size())
         * @throws std::runtime_error текущий носимый вес + новый предмет больше maxWeight.
         */
        void take_item(InventoryNS::Inventory &inventory, int index);

        /*!
         * Переместить предмет в инвентарь оперативника.
         * @param new_item указатель на предмет для перемещения.
         */
        void put_item(std::unique_ptr<ItemNS::Item> &&new_item);

        /*!
         * @brief Выбросить предмет под index'ом из инвентаря Оперативника.
         * @param index индекс предмета, который нужно сбросить
         * @return указатель на сброшенный предмет
         * @throws index not in [0, Inventory_.size())
         */
        std::unique_ptr<ItemNS::Item> throw_item(int index);

        ItemNS::Item *item_to_use(int index);

        /*!
         * @brief Перезарядить оружие.
         * @param container контейнер, из которого брать патроны для перезрядки.
         * @throws std::runtime_error, если нет активного оружия или мало времени на выполнение действия.
         * @details curTime_ становится меньше на max(ReloadTime_, ActiveWeapon_->getReloadTime());
         */
        void reload(RoundNS::RoundContainer &container);

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
         * @return инвентарь персонажа+добавленное активное оружие при наличии
         */
        std::optional<InventoryNS::Inventory> die() override;

        [[nodiscard]] int getReloadTime() const;

        void setReloadTime(int reloadTime);

        [[nodiscard]] int getMaxWeight() const;

        void setMaxWeight(int maxWeight);

        [[nodiscard]] int getAccuracy() const;

        void setAccuracy(int accuracy);
        /*!
         * Устанавливает инвентарь.
         * @param invetnory - инвентраь, которым нужно инициализировать инвентарь Оперативника.
         * @throws std::runtime_error если инвентарь слишком тяжел для оперативника.
         */
        void setInvetnory(InventoryNS::Inventory &&invetnory);
        /*!
         * Устанавливает активное оружие.
         * @param weapon - weapon, которым нужно инициализировать Activeweapon Оперативника.
         * @throws std::runtime_error если оружие слишком тяжело для оперативника.
         */
        void setActiveWeapon(WeaponNS::Weapon &weapon);

        [[nodiscard]] std::string getActiveWeaponTitle() const;

        [[nodiscard]] int getCurrentWeight() const;

    private:

        std::unique_ptr<WeaponNS::Weapon> ActiveWeapon_;
        InventoryNS::Inventory Inventory_;
        int ReloadTime_ = 2;
        int maxWeight_ = 15;
        int Accuracy_ = 100; // 1...100

    };
}

#endif //LAB3_OPERATIVE_H
