//
// Created by Master on 17.10.2023.
//

#include "Operative.h"


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

EntityNS::EntityType EntityNS::Operative::getType() const {
    return OPERATIVE;
}


EntityNS::Operative::Operative(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime,
                               int avaliableTime,
                               int stepTime, int visibilityRadius, int reloadTime, int maxWeight, int accuracy)
        : Entity(name, maxHeatPoint, curHeatPoint, curTime, avaliableTime, stepTime, visibilityRadius),
          ReloadTime_(reloadTime), maxWeight_(maxWeight), Accuracy_(accuracy) {}

void EntityNS::Operative::setInvetnory(InventoryNS::Inventory &&invetnory) {
    int weapon_weight = (ActiveWeapon_) ? ActiveWeapon_->getWeight() : 0;
    if (invetnory.getCurWeight() + weapon_weight > maxWeight_) {
        throw std::runtime_error("Player too weak to carry this inventory now.");
    }
    Inventory_ = std::move(invetnory);
}

void EntityNS::Operative::setActiveWeapon(WeaponNS::Weapon &weapon) {
    if (weapon.getWeight() + Inventory_.getCurWeight() > maxWeight_) {
        throw std::runtime_error("Player too weak to carry this weapon now.");
    }
    ActiveWeapon_ = std::make_unique<WeaponNS::Weapon>(weapon);
}

void EntityNS::Operative::change_weapon(int index) {
    if (index >= Inventory_.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }

    if ((*(Inventory_.begin() + index))->GetType() != ItemNS::ItemType::WEAPON) {
        throw std::invalid_argument("No weapon under given index.");
    }
    auto ptr_weapon_from_inventory = Inventory_.throw_item(Inventory_.begin() + index).release();
    auto ptr_new_active = dynamic_cast<WeaponNS::Weapon *>(ptr_weapon_from_inventory);

    if (ActiveWeapon_) {
        Inventory_.push_back(std::move(ActiveWeapon_));
    }
    ActiveWeapon_.reset(ptr_new_active);
}

std::string EntityNS::Operative::getActiveWeaponTitle() const {
    return ActiveWeapon_->GetTitle();
}


int EntityNS::Operative::getCurrentWeight() const {
    if (ActiveWeapon_) {
        return Inventory_.getCurWeight() + ActiveWeapon_->getWeight();
    } else {
        return Inventory_.getCurWeight();
    }

}

void EntityNS::Operative::take_item(InventoryNS::Inventory &inventory, int index) {
    if (index >= inventory.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }
    auto &tempPtr = *(inventory.begin() + index);
    if (tempPtr->getWeight() + this->getCurrentWeight() > maxWeight_) {
        throw std::runtime_error("Player too weak to carry this item now.");
    }
    auto ptr = inventory.throw_item(inventory.begin() + index);
    this->Inventory_.push_back(std::move(ptr));
}

void EntityNS::Operative::move(int new_i, int new_j) {
    if (curTime_ < StepTime_) {
        throw std::runtime_error("Too little time to perform the operation.");
    }
    if ((std::abs(new_i - i) + std::abs(new_j - j)) > 1) {
        throw std::invalid_argument("New position is too far from old.");
    }
    i = new_i;
    j = new_j;
    curTime_ -= StepTime_;
}

std::optional<InventoryNS::Inventory> EntityNS::Operative::die() {
    if (curHeatPoint_ > 0) {
        throw std::runtime_error("Player HP level is positive.");
    }
    if (ActiveWeapon_) {
        Inventory_.push_back(std::move(ActiveWeapon_));
    }
    auto drop_out = std::make_optional<InventoryNS::Inventory>(std::move(Inventory_));
    return drop_out;
}

std::unique_ptr<ItemNS::Item> EntityNS::Operative::throw_item(int index) {
    if (index >= Inventory_.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }
    return Inventory_.throw_item(Inventory_.begin() + index);
}

void EntityNS::Operative::reload(RoundNS::RoundContainer &container) {
    if (ActiveWeapon_ == nullptr) {
        throw std::runtime_error("No active weapon is chosen.");
    }
    if (curTime_ < std::max(ReloadTime_, ActiveWeapon_->getReloadTime())) {
        throw std::runtime_error("Too little time to perform the operation.");
    }
    ActiveWeapon_->reload(container);
    curTime_ -= std::max(ReloadTime_, ActiveWeapon_->getReloadTime());
}

bool EntityNS::Operative::shot(EntityNS::Entity &enemy) {
    if (ActiveWeapon_ == nullptr) {
        throw std::runtime_error("No active weapon is chosen.");
    }
    if (curTime_ < ActiveWeapon_->getShotTime()) {
        throw std::runtime_error("Too little time to perform the operation.");
    }
    int success_probability = rand() % 100 + 1;
    if (success_probability <= Accuracy_) {
        enemy.decrease_hp(ActiveWeapon_->shot());
        curTime_ -= ActiveWeapon_->getShotTime();
        return true;
    }
    curTime_ -= ActiveWeapon_->getShotTime();
    return false;

}

void EntityNS::Operative::put_item(std::unique_ptr<ItemNS::Item> &&new_item) {
    Inventory_.push_back(std::move(new_item));
}

ItemNS::Item *EntityNS::Operative::item_to_use(int index) {
    return (Inventory_.find(index))->get();
}












