//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_WEAPON_H
#define LAB3_WEAPON_H

#include "Item.h"
#include "RoundContainer.h"

namespace WeaponNS {
    /*!
	\brief Оружие. Наследник класса Item.
    */
    class Weapon : public ItemNS::Item {
    public:
        /*!
         * @brief Конструктор Weapon
         * @param title - название оружия
         * @param roundType - тип патронов
         * @param weight - вес оружия
         * @param magazineSize - количество патронов в магазине
         * @param damage - наносимый урон
         * @param shotTime - время выстрела
         * @param reloadTime - время перезарядки
         * @param magazineCapacity - вместимость магазина
         *
         */
        explicit Weapon(const std::string &title, int roundType, int weight=3, int magazineSize=0, int damage=3, int shotTime=1, int reloadTime=5,
               int magazineCapacity=10);
        /*!
         * @brief Метод для перезарядки - "сменить обойму"
         * @param container - контейнер для перезарядки
         * @throws std::runtime_error - в случае, если тип патронов оружия != типу патронов контейнера.
         * @details MagazineSize становится равным MagazineCapacity - MagazineSize
         */

        void reload(RoundNS::RoundContainer &container);
        /*!
         * @brief Метод нажатия на курок
         * @return наносимый урон в случае успеха
         * @throws std::runtime_error при отсутствии патронов в магазине
         * @details Уменьшает MagazineSize на 1
         */
        int shot();

        [[nodiscard]] int getMagazineSize() const;

        [[nodiscard]] int getDamage() const;

        [[nodiscard]] int getShotTime() const;

        [[nodiscard]] int getReloadTime() const;

        void setDamage(int damage);

        void setShotTime(int shotTime);

        void setReloadTime(int reloadTime);

        void setMagazineSize(int magazineSize);

        void setMagazineCapacity(int magazineCapacity);

        void setRoundType(int roundType);

        [[nodiscard]] ItemNS::ItemType GetType() const override;

    private:
        int Damage_;
        int ShotTime_;
        int ReloadTime_;
        int MagazineSize_;
        int MagazineCapacity_;
        int RoundType_;
    };

} // WeaponNS

#endif //LAB3_WEAPON_H
