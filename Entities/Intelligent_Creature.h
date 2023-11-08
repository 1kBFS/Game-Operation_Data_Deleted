//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_INTELLIGENT_CREATURE_H
#define LAB3_INTELLIGENT_CREATURE_H
#include "Entity.h"
#include "../Items/Weapon.h"
namespace EntityNS {

    class IntelligentCreature: public Entity {
    public:
        explicit IntelligentCreature(const std::string &name, int accuracy=75);

        [[nodiscard]] EntityType getType() const override;

        void move(int new_i, int new_j) override;

        std::optional<InventoryNS::Inventory> die() override;

        bool shot(EntityNS::Entity &enemy);

        std::unique_ptr<ItemNS::Item> throw_weapon();

        void put_weapon(std::unique_ptr<WeaponNS::Weapon>&& new_item);

        void take_item(InventoryNS::Inventory &inventory, int index);

    private:
        int Accuracy_;
        std::unique_ptr<WeaponNS::Weapon> ActiveWeapon_;
    };

} // EntityNS

#endif //LAB3_INTELLIGENT_CREATURE_H
