//
// Created by Master on 17.10.2023.
//

#include "Operative.h"

Operative::Operative(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime,
                     int stepTime, int visibilityRadius, int reloadTime, int maxWeight, int accuracy,
                     const InventoryNS::Inventory &invetnory, const std::optional<WeaponNS::Weapon> &activeWeapon)
        : Entity(name, maxHeatPoint, curHeatPoint, curTime, avaliableTime, stepTime, visibilityRadius),
          ReloadTime_(reloadTime), maxWeight_(maxWeight), Accuracy_(accuracy), Inventory_(invetnory),
          ActiveWeapon_(activeWeapon) {}

int Operative::getReloadTime() const {
    return ReloadTime_;
}

void Operative::setReloadTime(int reloadTime) {
    ReloadTime_ = reloadTime;
}

int Operative::getMaxWeight() const {
    return maxWeight_;
}

void Operative::setMaxWeight(int maxWeight) {
    maxWeight_ = maxWeight;
}

int Operative::getAccuracy() const {
    return Accuracy_;
}

void Operative::setAccuracy(int accuracy) {
    Accuracy_ = accuracy;
}

const InventoryNS::Inventory &Operative::getInvetnory() const {
    return Inventory_;
}

void Operative::setInvetnory(const InventoryNS::Inventory &invetnory) {
    Inventory_ = invetnory;
}

const std::optional<WeaponNS::Weapon> &Operative::getActiveWeapon() const {
    return ActiveWeapon_;
}

void Operative::setActiveWeapon(const std::optional<WeaponNS::Weapon> &activeWeapon) {
    ActiveWeapon_ = activeWeapon;
}
