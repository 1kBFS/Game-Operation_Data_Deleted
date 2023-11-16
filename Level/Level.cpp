//
// Created by Pavel on 15.10.2023.
//

#include <queue>
#include <map>
#include "Level.h"

namespace LevelNS {


    void Level::place_unit(std::pair<int, int> new_pos, std::shared_ptr<EntityNS::Entity> &entity) {
        if (!check_coords(new_pos)) {
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
        if (!check_coords(new_pos)) {
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
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].setType(type);
    }

    void Level::place_item_ground(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_item_ground(std::move(new_item));
    }

    void Level::place_item_container(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item> &&new_item) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_item_container(std::move(new_item));
    }

    void Level::place_all_items_ground(std::pair<int, int> pos, InventoryNS::Inventory &inventory) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_all_items_ground(inventory);
    }

    void Level::place_all_items_container(std::pair<int, int> pos, InventoryNS::Inventory &inventory) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].place_all_items_container(inventory);
    }

    void Level::remove_item_ground(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].remove_item_ground(index);

    }

    void Level::remove_item_container(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        Board_[pos.first][pos.second].remove_item_container(index);
    }

    std::vector<ItemNS::Item *> Level::show_items_ground(std::pair<int, int> pos) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].show_items_ground();
    }

    std::vector<ItemNS::Item *> Level::show_items_container(std::pair<int, int> pos)  {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].show_items_container();
    }

    std::unique_ptr<ItemNS::Item> Level::take_item_ground(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].take_item_ground(index);
    }

    std::unique_ptr<ItemNS::Item> Level::take_item_container(std::pair<int, int> pos, int index) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].take_item_container(index);
    }

    Level::Level(int size) {
        for (int i = 0; i < size; i++) {
            Board_.emplace_back(size);
        }
    }

    std::vector<std::pair<int, int>> Level::getCellsOnLine(std::pair<int, int> start_pos, std::pair<int, int> end_pos) {
        std::vector<std::pair<int, int>> result;
        int x1 = start_pos.first, y1 = start_pos.second;
        int x2 = end_pos.first, y2 = end_pos.second;
        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;
        int error = deltaX - deltaY;
        result.emplace_back(x2, y2);
        while (x1 != x2 || y1 != y2) {
            result.emplace_back(x1, y1);
            int error2 = error * 2;
            if (error2 > -deltaY) {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX) {
                error += deltaX;
                y1 += signY;
            }
        }
        return result;
    }

    std::vector<std::pair<int, int>> Level::getVisibleCells(std::pair<int, int> start_pos, int radius) const{
        const int plusX[4] = {0, 0, 1, -1};
        const int plusY[4] = {1, -1, 0, 0};
        std::queue<std::pair<int, int>> q;
        std::map<std::pair<int, int>, int> dist;
        dist[start_pos] = 0;
        q.push(start_pos);
        std::vector<std::pair<int, int>> potential_cells, result;
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            if (dist[v] > radius) {
                break;
            }
            potential_cells.push_back(v);
            for (int k = 0; k < 4; k++) {
                int x = v.first + plusX[k];
                int y = v.second + plusY[k];
                if (check_coords({x, y}) && !dist.contains({x, y})) {
                    dist[{x, y}] = dist[v] + 1;
                    q.push({x, y});
                }
            }
        }

        for (auto &cell: potential_cells) {
            auto cells_on_path = getCellsOnLine(start_pos, cell);
            if (check_all(cells_on_path, Cell::isVisiable)) {
                result.push_back(cell);
            }
        }
        return result;

    }

    bool Level::check_all(std::vector<std::pair<int, int>> &cells, const std::function<bool(const Cell &)> &checker)  const{
        for (auto &[i, j]: cells) {
            if (!checker(Board_[i][j])) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::shared_ptr<EntityNS::Entity>>
    Level::find_enemy(std::shared_ptr<EntityNS::Entity> &my_entity, TeamNS::Team &my_team,
                      std::vector<std::pair<int, int>> &visiably_cells) {
        std::vector<std::shared_ptr<EntityNS::Entity>> result;
        for (auto &[i, j]: visiably_cells) {
            auto &cell = Board_[i][j];
            for (auto &unit: cell) {
                if (my_team.find(unit) == my_team.end()) {
                    result.push_back(unit);
                }
            }
        }
        return result;
    }

    std::vector<std::pair<int, int>> Level::find_container() {
        std::vector<std::pair<int, int>> result;
        for (size_t i = 0; i < Board_.size(); i++) {
            for (size_t j = 0; j < Board_[0].size(); j++) {
                if (Board_[i][j].getType() == CONTAINER) {
                    result.emplace_back(i, j);
                }
            }
        }
        return result;
    }

    CellType Level::getCellType(std::pair<int, int> pos) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].getType();
    }

    InventoryNS::Inventory *Level::get_inventory_ground(std::pair<int, int> pos) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].get_inventory_ground();
    }

    InventoryNS::Inventory *Level::get_inventory_container(std::pair<int, int> pos) {
        if (!check_coords(pos)) {
            throw std::out_of_range("Invalid coords");
        }
        return Board_[pos.first][pos.second].get_inventory_container();
    }


} // LevelNS