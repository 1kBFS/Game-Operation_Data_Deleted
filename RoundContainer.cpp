//
// Created by Master on 12.10.2023.
//

#include "RoundContainer.h"

namespace RoundNS {
    RoundContainer::RoundContainer(const std::string &title, int roundType, int size, int weight, int capacity) : Item(
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

    int RoundContainer::extract(int amount){
        if (amount <= 0) {
            throw std::invalid_argument("Unable to extract negative amount of bullets.(Maybe, your weapon is already reloaded?)");
        }
        if (Size_ <= 0) {
            throw std::runtime_error("Container is empty.");
        }
        int extracted_value = std::min(amount, Size_);
        Size_-= extracted_value;
        return extracted_value;
    }
} // RoundNS