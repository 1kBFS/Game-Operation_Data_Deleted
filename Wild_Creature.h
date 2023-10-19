//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_WILD_CREATURE_H
#define LAB3_WILD_CREATURE_H
#include "Entity.h"
namespace EntityNS {

    class WildCreature:Entity {
        EntityType getType() const override;

        void move(int new_i, int new_j) override;

        std::optional<InventoryNS::Inventory> die() override;

        ~WildCreature() override = default;

        void shot(EntityNS::Entity &enemy);


    private:
        int Damage_;
        int Accuracy_;
    };

} // EntityNS

#endif //LAB3_WILD_CREATURE_H
