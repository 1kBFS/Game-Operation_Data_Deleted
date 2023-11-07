//
// Created by Pavel on 11.10.2023.
//

#include "Weapon.h"

namespace WeaponNS {
    int Weapon::getDamage() const {
        return Damage_;
    }

    Weapon::Weapon(const std::string &title, int roundType, int weight, int damage, int shotTime, int reloadTime, int magazineSize,
                   int magazineCapacity) : Item(title, weight), Damage_(damage), ShotTime_(shotTime),
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

    void Weapon::setDamage(int damage) {
        Damage_ = damage;
    }

    void Weapon::setShotTime(int shotTime) {
        ShotTime_ = shotTime;
    }

    void Weapon::setReloadTime(int reloadTime) {
        ReloadTime_ = reloadTime;
    }

    void Weapon::setMagazineSize(int magazineSize) {
        MagazineSize_ = magazineSize;
    }

    void Weapon::setMagazineCapacity(int magazineCapacity) {
        MagazineCapacity_ = magazineCapacity;
    }

    void Weapon::setRoundType(int roundType) {
        RoundType_ = roundType;
    }

    void Weapon::reload(RoundNS::RoundContainer &container) {
        if (container.getRoundType() != RoundType_) {
            throw std::runtime_error("Invalid container type. Rounds are different.");
        }
        MagazineSize_+=container.extract(MagazineCapacity_ - MagazineSize_);
    }

    int Weapon::shot() {
        if (MagazineSize_ <= 0) {
            throw std::runtime_error("Weapon magazine is empty");
        }
        MagazineSize_-=1;
        return Damage_;
    }
} // WeaponNS