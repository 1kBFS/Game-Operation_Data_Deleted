//
// Created by Master on 12.10.2023.
//

#include "RoundContainer.h"

namespace RoundNS {
    RoundContainer::RoundContainer(const std::string &title, int weight, int roundType, int capacity, int size) : Item(
            title, weight), RoundType_(roundType), Capacity_(capacity), Size_(size) {}

    int RoundContainer::getRoundType() const {
        return RoundType_;
    }

    int RoundContainer::getCapacity() const {
        return Capacity_;
    }

    int RoundContainer::getSize() const {
        return Size_;
    }

    void RoundContainer::setRoundType(int roundType) {
        RoundType_ = roundType;
    }

    void RoundContainer::setCapacity(int capacity) {
        Capacity_ = capacity;
    }

    void RoundContainer::setSize(int size) {
        Size_ = size;
    }

    ItemNS::ItemType RoundContainer::GetType() const {
        return ItemNS::CONTAINER;
    }
} // RoundNS