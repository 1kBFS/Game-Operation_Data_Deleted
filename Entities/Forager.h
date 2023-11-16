//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_FORAGER_H
#define LAB3_FORAGER_H
#include "Entity.h"
namespace EntityNS {
    class Forager: public Entity {
    public:
        explicit Forager(const std::string &name);

        void drop_all(InventoryNS::Inventory &inventory);

        // index in unit inventory
        void drop_into(InventoryNS::Inventory &inventory, int index);

        void take_item(InventoryNS::Inventory &inventory, int index);

        std::unique_ptr<ItemNS::Item> throw_item(int index);

        [[nodiscard]] EntityType getType() const override;

        void move(int new_i, int new_j) override;

        std::optional<InventoryNS::Inventory> die() override;

        void setInvetnory(InventoryNS::Inventory &&invetnory);
    private:
        InventoryNS::Inventory Inventory_;
    };
}

#endif //LAB3_FORAGER_H
