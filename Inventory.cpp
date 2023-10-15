//
// Created by Master on 12.10.2023.
//

#include "Inventory.h"

namespace InventoryNS {
    Inventory::Inventory(const Inventory &) {

    }

    InventoryIterator::InventoryIterator(std::vector<std::unique_ptr<ItemNS::Item>>::iterator it) {

    }

    bool InventoryIterator::operator==(const InventoryIterator &rhs) const {
        return Iterator_ == rhs.Iterator_;
    }

    bool InventoryIterator::operator!=(const InventoryIterator &rhs) const {
        return !(rhs == *this);
    }
} // InventoryNS