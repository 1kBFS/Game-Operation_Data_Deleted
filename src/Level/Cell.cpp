//
// Created by Pavel on 15.10.2023.
//

#include "Cell.h"

namespace CellNS {
} // CellNS
void LevelNS::Cell::place_item_ground(std::unique_ptr<ItemNS::Item> &&new_item) {
    if (can_be_placed()) {
        ItemsGround_.push_back(std::move(new_item));
    } else {
        throw std::invalid_argument("Bad cell type");
    }
}

void LevelNS::Cell::place_item_container(std::unique_ptr<ItemNS::Item> &&new_item) {
    if (Type_ == CONTAINER) {
        ItemsContainer_.push_back(std::move(new_item));
    } else {
        throw std::invalid_argument("Bad cell type");
    }
}

void LevelNS::Cell::remove_item_ground(int index) {
    if (index < 0 || index >= ItemsGround_.getSize()) {
        throw std::out_of_range("Invalid index");
    }
    ItemsGround_.erase(ItemsGround_.begin() + index);
}

void LevelNS::Cell::remove_item_container(int index) {
    if (index < 0 || index >= ItemsContainer_.getSize()) {
        throw std::out_of_range("Invalid index");
    }
    ItemsContainer_.erase(ItemsContainer_.begin() + index);
}

void LevelNS::Cell::place_unit(std::shared_ptr<EntityNS::Entity> &entity) {
    if (can_be_placed()) {
        Entities_.push_back(entity);
    } else {
        throw std::invalid_argument("Bad cell type");
    }
}

bool LevelNS::Cell::can_be_placed() const {
    return (Type_ == FLOOR || Type_ == CONTAINER);
}

LevelNS::Cell::CellEntitiesIterator LevelNS::Cell::begin() {
    return Entities_.begin();
}

LevelNS::Cell::CellEntitiesIterator LevelNS::Cell::end() {
    return Entities_.end();
}

void LevelNS::Cell::remove_unit(LevelNS::Cell::CellEntitiesIterator pos) {
    Entities_.erase(pos);
}

bool LevelNS::Cell::is_same_entities(const std::shared_ptr<EntityNS::Entity> &lhs,
                                     const std::shared_ptr<EntityNS::Entity> &rhs) {
    if (lhs == rhs) {
        return true;
    }
    if (lhs && rhs) {
        return lhs.get() == rhs.get();
    }
    return false;
}

LevelNS::Cell::CellEntitiesIterator LevelNS::Cell::find_unit(std::shared_ptr<EntityNS::Entity> &entity_to_find) {
    for (auto it = Entities_.begin(); it != Entities_.end(); it++) {
        if (is_same_entities(*it, entity_to_find)) {
            return it;
        }
    }
    return end();
}

void LevelNS::Cell::place_all_items_ground(InventoryNS::Inventory &inventory) {
    if (can_be_placed()) {
        ItemsGround_.put_all(inventory);
    } else {
        throw std::invalid_argument("Bad cell type");
    }
}

void LevelNS::Cell::place_all_items_container(InventoryNS::Inventory &inventory) {
    if (Type_ == CONTAINER) {
        ItemsContainer_.put_all(inventory);
    } else {
        throw std::invalid_argument("Bad cell type");
    }
}

LevelNS::CellType LevelNS::Cell::getType() const {
    return Type_;
}

void LevelNS::Cell::setType(LevelNS::CellType type) {
    Type_ = type;
}

std::vector<const ItemNS::Item *> LevelNS::Cell::show_items_ground() const{
    return ItemsGround_.show_items();
}

std::vector<const ItemNS::Item *> LevelNS::Cell::show_items_container() const{
    return ItemsContainer_.show_items();
}

std::unique_ptr<ItemNS::Item> LevelNS::Cell::take_item_ground(int index) {
    if (index < 0 || index >= ItemsGround_.getSize()) {
        throw std::out_of_range("Invalid index");
    }
    return ItemsGround_.throw_item(ItemsGround_.begin() + index);
}

std::unique_ptr<ItemNS::Item> LevelNS::Cell::take_item_container(int index) {
    if (index < 0 || index >= ItemsContainer_.getSize()) {
        throw std::out_of_range("Invalid index");
    }
    return ItemsContainer_.throw_item(ItemsContainer_.begin() + index);
}

InventoryNS::Inventory *LevelNS::Cell::get_inventory_ground() {
    return &ItemsGround_;
}

InventoryNS::Inventory *LevelNS::Cell::get_inventory_container(){
    return &ItemsContainer_;
}

LevelNS::Cell::const_CellEntitiesIterator LevelNS::Cell::begin() const {
    return Entities_.begin();
}

LevelNS::Cell::const_CellEntitiesIterator LevelNS::Cell::end() const {
    return Entities_.end();
}




