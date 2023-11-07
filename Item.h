//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

#include <string>
#include <iostream>
#include <utility>

namespace ItemNS {

    enum ItemType {
        WEAPON, AID_KIT, CONTAINER
    };

    class Item {
    public:
        Item(std::string title, int weight);

        [[nodiscard]] const std::string &GetTitle() const {
            return Title_;
        }

        [[nodiscard]] virtual ItemType GetType() const = 0;

        virtual ~Item() = default;

    private:
        std::string Title_;
        int Weight_;
    };


} // ItemNS

#endif //LAB3_ITEM_H
