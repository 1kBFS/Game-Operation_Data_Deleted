//
// Created by Master on 17.10.2023.
//

#include "Operative.h"

EntityNS::Operative::Operative(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime,
                     int stepTime, int visibilityRadius, int reloadTime, int maxWeight, int accuracy,
                     const InventoryNS::Inventory &invetnory, const std::optional<WeaponNS::Weapon> &activeWeapon)
        : Entity(name, maxHeatPoint, curHeatPoint, curTime, avaliableTime, stepTime, visibilityRadius),
          ReloadTime_(reloadTime), maxWeight_(maxWeight), Accuracy_(accuracy), Inventory_(invetnory),
          ActiveWeapon_(activeWeapon) {}

int EntityNS::Operative::getReloadTime() const {
    return ReloadTime_;
}

void EntityNS::Operative::setReloadTime(int reloadTime) {
    ReloadTime_ = reloadTime;
}

int EntityNS::Operative::getMaxWeight() const {
    return maxWeight_;
}

void EntityNS::Operative::setMaxWeight(int maxWeight) {
    maxWeight_ = maxWeight;
}

int EntityNS::Operative::getAccuracy() const {
    return Accuracy_;
}

void EntityNS::Operative::setAccuracy(int accuracy) {
    Accuracy_ = accuracy;
}

//const InventoryNS::Inventory &EntityNS::Operative::getInvetnory() const {
//    return Inventory_;
//}

void EntityNS::Operative::setInvetnory(const InventoryNS::Inventory &invetnory) {
    Inventory_ = invetnory;
}

const std::optional<WeaponNS::Weapon> &EntityNS::Operative::getActiveWeapon() const {
    return ActiveWeapon_;
}

void EntityNS::Operative::setActiveWeapon(const std::optional<WeaponNS::Weapon> &activeWeapon) {
    ActiveWeapon_ = activeWeapon;
}

EntityNS::EntityType EntityNS::Operative::getType() const {
    return OPERATIVE;
}

void EntityNS::Operative::move(int new_i, int new_j) {

}


