//
// Created by Master on 12.10.2023.
//

#include "Inventory.h"

namespace InventoryNS {
    Inventory::Inventory(const Inventory &) {

    }

    int Inventory::getSize() const {
        return static_cast<int>(Elements_.size());
    }

    int Inventory::getCurWeight() const {
        return curWeight;
    }
} // InventoryNS