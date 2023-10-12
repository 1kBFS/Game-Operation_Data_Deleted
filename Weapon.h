//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_WEAPON_H
#define LAB3_WEAPON_H
#include "Item.h"
namespace WeaponNS {

    class Weapon : public ItemNS::Item {
    public:
        Weapon(const std::string &title, int weight, int damage, int shotTime, int reloadTime, int magazineSize,
               int magazineCapacity, int cartridgeType);

        int getDamage() const;

    private:
        int Damage_;
        int ShotTime_;
        int ReloadTime_;
        int MagazineSize_;
        int MagazineCapacity_;
        int CartridgeType_;
    };

} // WeaponNS

#endif //LAB3_WEAPON_H
