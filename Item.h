//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

#include <string>
#include <iostream>
#include <utility>

namespace ItemNS {

    class Item {
    public:
        Item(std::string title, int weight);

        const std::string &GetTitle() const {
            return Title_;
        }

    private:
        std::string Title_;
        int Weight_;
    };

} // ItemNS

#endif //LAB3_ITEM_H
