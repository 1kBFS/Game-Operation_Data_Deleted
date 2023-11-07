//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_WEAPON_H
#define LAB3_WEAPON_H

#include "Item.h"
#include "RoundContainer.h"

namespace WeaponNS {

    class Weapon : public ItemNS::Item {
    public:

        explicit Weapon(const std::string &title, int roundType, int weight=3, int damage=3, int shotTime=1, int reloadTime=5, int magazineSize=0,
               int magazineCapacity=10);

        void reload(RoundNS::RoundContainer &container);

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
