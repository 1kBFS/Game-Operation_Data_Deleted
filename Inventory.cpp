//
// Created by Master on 12.10.2023.
//

#include "Inventory.h"

namespace InventoryNS {


    int Inventory::getSize() const {
        return static_cast<int>(Elements_.size());
    }

    int Inventory::getCurWeight() const {
        return curWeight;
    }

    Inventory::Inventory(Inventory &&inventory) noexcept{
        curWeight = inventory.curWeight;
        inventory.curWeight = 0;
        Elements_ = std::move(inventory.Elements_);
    }

    Inventory &Inventory::operator=(Inventory &&inventory) noexcept{
        curWeight = inventory.curWeight;
        inventory.curWeight = 0;
        Elements_ = std::move(inventory.Elements_);
        return *this;
    }

    void Inventory::push_back(std::unique_ptr<ItemNS::Item>&& new_item) {
        curWeight += new_item->getWeight();
        Elements_.push_back(std::move(new_item));
    }

    Inventory::const_InventoryIterator Inventory::begin() const {
        return Elements_.begin();
    }

    Inventory::const_InventoryIterator Inventory::end() const {
        return Elements_.end();
    }

    Inventory::InventoryIterator Inventory::find(const std::string &title) {

        for (auto it = Elements_.begin(); it != Elements_.end(); it++){
            if ((*it)->GetTitle() == title){
                return it;
            }
        }
        return Elements_.end();
    }

    Inventory::InventoryIterator Inventory::begin() {
        return Elements_.begin();
    }

    Inventory::InventoryIterator Inventory::end() {
        return Elements_.end();
    }

    void Inventory::erase(Inventory::InventoryIterator pos) {
        curWeight-=(*pos)->getWeight();
        Elements_.erase(pos);
    }

    void Inventory::put_all(Inventory &inventory) {
        for (auto& el : inventory){
            this->push_back(std::move(el));
        }
        inventory.Elements_.clear();
        inventory.curWeight = 0;
    }

    std::unique_ptr<ItemNS::Item> Inventory::throw_item(Inventory::InventoryIterator pos) {
        curWeight-=(*pos)->getWeight();
        std::unique_ptr<ItemNS::Item> ptr = std::move(*pos);
        Elements_.erase(pos);
        return ptr;
    }




} // InventoryNS