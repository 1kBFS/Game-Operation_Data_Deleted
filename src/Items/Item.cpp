//
// Created by Pavel on 11.10.2023.
//

#include "Item.h"

namespace ItemNS {
    Item::Item(std::string title, int weight) : Title_(std::move(title)) {
        if (weight < 0) throw std::invalid_argument("Weight is non-negative. ");
        Weight_ = weight;
    }

    int Item::getWeight() const {
        return Weight_;
    }

} // ItemNS