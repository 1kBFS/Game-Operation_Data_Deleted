//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_WILD_CREATURE_H
#define LAB3_WILD_CREATURE_H
#include "Entity.h"
namespace EntityNS {

    class WildCreature: public Entity {
    public:
        explicit WildCreature(const std::string &name, int damage=1, int accuracy=75);

        [[nodiscard]] EntityType getType() const override;

        void move(int new_i, int new_j) override;

        std::optional<InventoryNS::Inventory> die() override;

        bool shot(EntityNS::Entity &enemy);

        ~WildCreature() override = default;

    private:
        int Damage_ = 1;
        int Accuracy_ = 75;
    };

} // EntityNS

#endif //LAB3_WILD_CREATURE_H
