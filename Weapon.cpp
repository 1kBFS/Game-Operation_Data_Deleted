//
// Created by Pavel on 11.10.2023.
//

#include "Weapon.h"

namespace WeaponNS {
    int Weapon::getDamage() const {
        return Damage_;
    }

    Weapon::Weapon(const std::string &title, int weight, int damage, int shotTime, int reloadTime, int magazineSize,
                   int magazineCapacity, int cartridgeType) : Item(title, weight), Damage_(damage), ShotTime_(shotTime),
                                                              ReloadTime_(reloadTime), MagazineSize_(magazineSize),
                                                              MagazineCapacity_(magazineCapacity),
                                                              CartridgeType_(cartridgeType) {}
} // WeaponNS