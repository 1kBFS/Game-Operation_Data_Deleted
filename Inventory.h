//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_INVENTORY_H
#define LAB3_INVENTORY_H

#include <memory>
#include <vector>
#include "Item.h"

namespace InventoryNS {

    class Inventory {
    public:
        typedef std::vector<std::unique_ptr<ItemNS::Item>>::iterator InventoryIterator;

        Inventory(const Inventory &);

        Inventory &operator=(const Inventory &);

        InventoryIterator find(const std::string &title);

        InventoryIterator replace(InventoryIterator pos, const ItemNS::Item &new_item);

        InventoryIterator erase(InventoryIterator pos);

        void push_back(const ItemNS::Item &new_item);

        InventoryIterator begin() const;

        InventoryIterator end() const;

        int getCurWeight() const;

        [[nodiscard]] int getSize() const;

    private:
        int curWeight;
        std::vector<std::unique_ptr<ItemNS::Item>> Elements_;
    };

} // InventoryNS

#endif //LAB3_INVENTORY_H
