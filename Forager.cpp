//
// Created by Pavel on 18.10.2023.
//

#include "Forager.h"

EntityNS::EntityType EntityNS::Forager::getType() const {
    return INTELLIGENT_CREATURE;
}

void EntityNS::Forager::move(int new_i, int new_j) {

}

std::optional<InventoryNS::Inventory> EntityNS::Forager::die() {
    return std::optional<InventoryNS::Inventory>();
}
