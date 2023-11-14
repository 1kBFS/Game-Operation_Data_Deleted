//
// Created by Pavel on 15.10.2023.
//

#include "Level.h"

namespace LevelNS {


    void Level::place_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity) {
        if (!check_coords(new_pos)){
            throw std::out_of_range("Invalid coords");
        }
        entity->setPos(new_pos);
        Board_[new_pos.first][new_pos.second].place_unit(entity);
    }


    bool Level::check_coords(std::pair<int, int> pos) const {
        return (((pos.first) < Board_.size() && pos.first >= 0) &&
                ((pos.second) < Board_[0].size() && pos.second >= 0));
    }

    void Level::remove_unit(std::shared_ptr<EntityNS::Entity> &entity) {
        auto pos = entity->getPos();
        auto it = Board_[pos.first][pos.second].find_unit(entity);
        if (it == Board_[pos.first][pos.second].end()) {
            throw std::runtime_error("No such entity");
        } else {
            Board_[pos.first][pos.second].remove_unit(it);
        }
    }

    void Level::move_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity) {
        if (!check_coords(new_pos)){
            throw std::out_of_range("Invalid coords");
        }
        auto pos = entity->getPos();
        auto it = Board_[pos.first][pos.second].find_unit(entity);
        if (it == Board_[pos.first][pos.second].end()) {
            throw std::runtime_error("No such entity");
        } else {
            entity->move(new_pos.first, new_pos.second);
            Board_[pos.first][pos.second].remove_unit(it);
            Board_[new_pos.first][new_pos.second].place_unit(entity);
        }


    }

    void Level::setCellType(std::pair<int, int> pos, CellType type) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].setType(type);
    }

    void Level::place_item_ground(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_item_ground(std::move(new_item));
    }

    void Level::place_item_container(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_item_container(std::move(new_item));
    }

    void Level::place_all_items_ground(std::pair<int, int> pos, InventoryNS::Inventory &inventory) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_all_items_ground(inventory);
    }

    void Level::place_all_items_container(std::pair<int, int> pos, InventoryNS::Inventory &inventory) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_all_items_container(inventory);
    }

    void Level::remove_item_ground(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].remove_item_ground(index);

    }

    void Level::remove_item_container(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].remove_item_container(index);
    }

    std::vector<const ItemNS::Item *> Level::show_items_ground(std::pair<int, int> pos) const {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].show_items_ground();
    }

    std::vector<const ItemNS::Item *> Level::show_items_container(std::pair<int, int> pos) const {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].show_items_container();
    }

    std::unique_ptr<ItemNS::Item> Level::take_item_ground(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].take_item_ground(index);
    }

    std::unique_ptr<ItemNS::Item> Level::take_item_container(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)){
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].take_item_container(index);
    }

    Level::Level(int size) {
        for (int i = 0; i < size; i++){
            Board_.emplace_back(size);
        }
    }

    void Level::findVisiably(int i, int j, int radius, std::vector<std::pair<int, int>> &result) {

    }


} // LevelNS