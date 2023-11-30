//
// Created by Pavel on 18.10.2023.
//

#include "Wild_Creature.h"

namespace EntityNS {
    EntityType WildCreature::getType() const {
        return WILD_CREATURE;
    }

    void WildCreature::move(int new_i, int new_j) {
        if (new_i < 0 || new_j < 0){
            throw std::invalid_argument("New location coord is positive");
        }
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

    std::optional<InventoryNS::Inventory> WildCreature::die() {
        if (curHeatPoint_ > 0) {
            throw std::runtime_error("Player HP level is positive.");
        }
        return std::nullopt;
    }

    bool WildCreature::shot(Entity &enemy) {
        if (enemy.getPos() != this->getPos()) {
            throw std::invalid_argument("The Enemy is not in the same cell.");
        }
        if (curTime_ < 1){
            throw std::runtime_error("Too little time to perform the operation.");
        }
        int success_probability = rand() % 100 + 1;
        if (success_probability <= Accuracy_) {
            enemy.decrease_hp(Damage_);
            curTime_-=1;
            return true;
        }
        curTime_-=1;
        return false;
    }

    WildCreature::WildCreature(const std::string &name, int damage, int accuracy) : Entity(name), Damage_(damage),
                                                                                    Accuracy_(accuracy) {}

} // EntityNS