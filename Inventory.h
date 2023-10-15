//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_INVENTORY_H
#define LAB3_INVENTORY_H

#include <memory>
#include <vector>
#include "Item.h"

namespace InventoryNS {
    class InventoryIterator {
    private:
        std::vector<std::unique_ptr<ItemNS::Item>>::iterator Iterator_;
    public:
        explicit InventoryIterator(){}
        explicit InventoryIterator(std::vector<std::unique_ptr<ItemNS::Item>>::iterator it);

        bool operator==(const InventoryIterator &rhs) const;

        bool operator!=(const InventoryIterator &rhs) const;

        & operator *();
        * operator ->();
    };

    class Inventory {
    public:
        Inventory(const Inventory &);

        Inventory &operator=(const Inventory &);

        friend class InventoryIterator;

        InventoryIterator find(const std::string &title);

        InventoryIterator replace(InventoryIterator pos, const ItemNS::Item &new_item);

        InventoryIterator erase(InventoryIterator pos);

        void push_back(const ItemNS::Item &new_item);

        InventoryIterator begin() const;

        InventoryIterator end() const;

        int getSize() const;

    private:
        std::vector<std::unique_ptr<ItemNS::Item>> Elements_;
    };

} // InventoryNS

#endif //LAB3_INVENTORY_H
