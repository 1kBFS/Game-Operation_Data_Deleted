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
        Weapon(const std::string &title, int weight, int damage, int shotTime, int reloadTime, int magazineSize,
               int magazineCapacity, int roundType);

        void reload(const RoundNS::RoundContainer &container);

        int shot();

        int getMagazineSize() const;

        int getDamage() const;

        int getShotTime() const;

        int getReloadTime() const;

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
