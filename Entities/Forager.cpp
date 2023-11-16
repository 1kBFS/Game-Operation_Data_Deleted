//
// Created by Pavel on 18.10.2023.
//

#include "Forager.h"

EntityNS::EntityType EntityNS::Forager::getType() const {
    return FORAGER;
}

void EntityNS::Forager::move(int new_i, int new_j) {
    if (curTime_ < StepTime_) {
        throw std::runtime_error("Too little time to perform the operation.");
    }
    if ((std::abs(new_i - i) + std::abs(new_j - j)) > 1) {
        throw std::invalid_argument("New position is too far from old.");
    }
    i = new_i;
    j = new_j;
    curTime_-=StepTime_;
}

std::optional<InventoryNS::Inventory> EntityNS::Forager::die() {
    if (curHeatPoint_ > 0) {
        throw std::runtime_error("Player HP level is positive.");
    }
    auto drop_out = std::make_optional<InventoryNS::Inventory>(std::move(Inventory_));
    return drop_out;
}

void EntityNS::Forager::take_item(InventoryNS::Inventory &inventory, int index) {
    if (index >= inventory.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }
    auto ptr = inventory.throw_item(inventory.begin()+index);
    this->Inventory_.push_back(std::move(ptr));
}

std::unique_ptr<ItemNS::Item> EntityNS::Forager::throw_item(int index) {
    if (index >= Inventory_.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }
    return Inventory_.throw_item(Inventory_.begin()+index);
}

// index in unit inventory
void EntityNS::Forager::drop_into(InventoryNS::Inventory &inventory, int index) {
    if (index >= Inventory_.getSize() || index < 0) {
        throw std::out_of_range("Invalid index.");
    }
    inventory.push_back(std::move(Inventory_.throw_item(Inventory_.begin()+index)));
}

void EntityNS::Forager::drop_all(InventoryNS::Inventory &inventory) {
    for (int i = 0; i < Inventory_.getSize(); i++)
        drop_into(inventory, i);
}

EntityNS::Forager::Forager(const std::string &name) : Entity(name) {}

void EntityNS::Forager::setInvetnory(InventoryNS::Inventory &&invetnory) {
    Inventory_ = std::move(invetnory);
}
