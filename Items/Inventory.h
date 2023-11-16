//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_INVENTORY_H
#define LAB3_INVENTORY_H

#include <memory>
#include <vector>
#include "Item.h"
// All Items are unique.
namespace InventoryNS {

    class Inventory {
    public:
        typedef std::vector<std::unique_ptr<ItemNS::Item>>::const_iterator const_InventoryIterator;
        typedef std::vector<std::unique_ptr<ItemNS::Item>>::iterator InventoryIterator;
        Inventory() = default;
        Inventory(const Inventory &) = delete;
        Inventory &operator=(const Inventory &) = delete;

        Inventory(Inventory &&) noexcept;
        Inventory& operator=(Inventory &&inventory) noexcept;

        InventoryIterator find(const std::string &title);

        InventoryIterator find(int index);
        void erase(InventoryIterator pos);

        void push_back(std::unique_ptr<ItemNS::Item>&& new_item);

        void put_all(Inventory& inventory);

        std::unique_ptr<ItemNS::Item> throw_item(InventoryIterator pos);

        [[nodiscard]] const_InventoryIterator begin() const;

        [[nodiscard]] const_InventoryIterator end() const;

        InventoryIterator begin();
        InventoryIterator end();

        [[nodiscard]] int getCurWeight() const;

        [[nodiscard]] int getSize() const;

        [[nodiscard]] std::vector<ItemNS::Item *> show_items();

    private:
        int curWeight = 0;
        std::vector<std::unique_ptr<ItemNS::Item>> Elements_;
    };

} // InventoryNS

#endif //LAB3_INVENTORY_H
