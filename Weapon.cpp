//
// Created by Pavel on 11.10.2023.
//

#include "Weapon.h"

namespace WeaponNS {
    int Weapon::getDamage() const {
        return Damage_;
    }

    Weapon::Weapon(const std::string &title, int weight, int damage, int shotTime, int reloadTime, int magazineSize,
                   int magazineCapacity, int roundType) : Item(title, weight), Damage_(damage), ShotTime_(shotTime),
                                                              ReloadTime_(reloadTime), MagazineSize_(magazineSize),
                                                              MagazineCapacity_(magazineCapacity),
                                                              RoundType_(roundType) {}

    int Weapon::getShotTime() const {
        return ShotTime_;
    }

    int Weapon::getReloadTime() const {
        return ReloadTime_;
    }

    int Weapon::getMagazineSize() const {
        return MagazineSize_;
    }

    ItemNS::ItemType Weapon::GetType() const {
        return ItemNS::WEAPON;
    }
} // WeaponNS