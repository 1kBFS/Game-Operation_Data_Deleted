//
// Created by Pavel on 18.10.2023.
//

#include "Intelligent_Creature.h"

namespace EntityNS {
    EntityType IntelligentCreature::getType() const {
        return INTELLIGENT_CREATURE;
    }

    void IntelligentCreature::move(int new_i, int new_j) {
        if (curTime_ < StepTime_) {
            throw std::runtime_error("Too little time to perform the operation.");
        }
        if ((std::abs(new_i - i) + std::abs(new_j - j)) > 1) {
            throw std::invalid_argument("New position is too far from old.");
        }
        i = new_i;
        j = new_j;
        curTime_-=StepTime_;
    }

    std::optional<InventoryNS::Inventory> IntelligentCreature::die() {
        if (curHeatPoint_ > 0) {
            throw std::runtime_error("Player HP level is positive.");
        }
        if (ActiveWeapon_) {
            InventoryNS::Inventory drop_out;
            drop_out.push_back(std::move(ActiveWeapon_));
            return std::make_optional<InventoryNS::Inventory>(std::move(drop_out));
        } else {
            return std::nullopt;
        }
    }

    bool IntelligentCreature::shot(Entity &enemy) {
        if (ActiveWeapon_ == nullptr) {
            throw std::runtime_error("No active weapon is chosen.");
        }
        if (curTime_ < ActiveWeapon_->getShotTime()){
            throw std::runtime_error("Too little time to perform the operation.");
        }
        int success_probability = rand() % 100 + 1;
        if (success_probability <= Accuracy_) {
            enemy.decrease_hp(ActiveWeapon_->shot());
            curTime_-=ActiveWeapon_->getShotTime();
            return true;
        }
        curTime_-=ActiveWeapon_->getShotTime();
        return false;
    }

    std::unique_ptr<ItemNS::Item> IntelligentCreature::throw_weapon() {
        std::unique_ptr<ItemNS::Item> ptr_thrown_item;
        auto ptr = ActiveWeapon_.release();
        ptr_thrown_item.reset(ptr);
        ActiveWeapon_.reset();
        return ptr_thrown_item;
    }

    void IntelligentCreature::put_weapon(std::unique_ptr<WeaponNS::Weapon> &&new_item) {
        if (ActiveWeapon_) {
            throw std::runtime_error("Unit already has weapon. Drop it out before.");
        }
        ActiveWeapon_ = std::move(new_item);
    }

    void IntelligentCreature::take_item(InventoryNS::Inventory &inventory, int index) {
        if (ActiveWeapon_) {
            throw std::runtime_error("Unit already has weapon. Drop it out before.");
        }
        if (index >= inventory.getSize() || index < 0) {
            throw std::out_of_range("Invalid index.");
        }
        auto& tempPtr = *(inventory.begin()+index);
        if (tempPtr->GetType() != ItemNS::WEAPON){
            throw std::invalid_argument("No weapon under given index.");
        }
        auto required_itemPtr = inventory.throw_item(inventory.begin()+index).release();
        std::unique_ptr<WeaponNS::Weapon> to_unit;
        auto required_itemPtr_casted = dynamic_cast<WeaponNS::Weapon *>(required_itemPtr);
        to_unit.reset(required_itemPtr_casted);
        ActiveWeapon_ = std::move(to_unit);

    }

    IntelligentCreature::IntelligentCreature(const std::string &name, int accuracy) : Entity(name),
                                                                                      Accuracy_(accuracy) {}


} // EntityNS