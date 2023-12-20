//
// Created by Pavel on 18.10.2023.
//

#include "Game.h"
#include "../Entities/Operative.h"
#include "../Entities/Forager.h"
#include "../Entities/Intelligent_Creature.h"
#include "../Entities/Wild_Creature.h"

#include "../Items/RoundContainer.h"
#include "../Items/FirstAidKit.h"
#include "../Items/Weapon.h"

namespace GameNS {
    Game::Game(int size, std::vector<TeamNS::Team> &&teams) : CurrentLevel_(size) {
        Teams_ = std::move(teams);
        ActiveTeam_ = Teams_.begin();
        ActivePlayer_ = ActiveTeam_->begin();
        for (auto &team: Teams_) {
            for (auto &unit: team) {
                CurrentLevel_.place_unit(unit->getPos(), unit);
            }
        }
    }

    void Game::reset_time() {
        for (auto &el: *ActiveTeam_) {
            el->reset_time();
        }
    }

    void Game::next_player() {
        ActivePlayer_++;
        if (ActivePlayer_ == ActiveTeam_->end()) {
            ActivePlayer_ = ActiveTeam_->begin();
        }
    }

    bool Game::next_team() {
        bool isGameOver = checkGameOver();
        if (isGameOver)
            return true;
        ActiveTeam_++;
        if (ActiveTeam_ == Teams_.end()) {
            ActiveTeam_ = Teams_.begin();
        }
        ActivePlayer_ = ActiveTeam_->begin();
        reset_time();
        return false;
    }

    void Game::move(std::pair<int, int> new_pos) {
        CurrentLevel_.move_unit(new_pos, *ActivePlayer_);
    }

    void Game::shot(std::pair<int, int> attack_pos, std::shared_ptr<EntityNS::Entity> &enemy) {
        auto cells_on_line = LevelNS::Level::getCellsOnLine((*ActivePlayer_)->getPos(), enemy->getPos());
        if (!CurrentLevel_.check_all(cells_on_line, LevelNS::Cell::isEmpty)) {
            if (CurrentLevel_.check_all(cells_on_line, LevelNS::Cell::isFragile)) {
                for (auto &cell: cells_on_line) {
                    auto type = CurrentLevel_.getCellType(cell);
                    if (type == LevelNS::WINDOW || type == LevelNS::BARRIER) {
                        CurrentLevel_.setCellType(cell, LevelNS::FLOOR);
                    }
                }
                return;
            } else {
                throw std::invalid_argument("The position is hidden behind objects that cannot be destroyed");
            }
        }
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            ptr_oper->shot(*enemy);
        } else if ((*ActivePlayer_)->getType() == EntityNS::WILD_CREATURE) {
            auto ptr_wild = dynamic_cast<EntityNS::WildCreature *>((*ActivePlayer_).get());
            ptr_wild->shot(*enemy);
        } else if ((*ActivePlayer_)->getType() == EntityNS::INTELLIGENT_CREATURE) {
            auto ptr_intel = dynamic_cast<EntityNS::IntelligentCreature *>((*ActivePlayer_).get());
            ptr_intel->shot(*enemy);
        } else {
            throw std::runtime_error("This type of entity unable to kill");
        }
        if (enemy->getCurHeatPoint() <= 0) {
            auto inventory = enemy->die();
            if (inventory.has_value()) {
                CurrentLevel_.place_all_items_ground(enemy->getPos(), inventory.value());
            }
            CurrentLevel_.remove_unit(enemy);
            for (auto &team: Teams_) {
                auto it = team.find(enemy);
                if (it != team.end()) {
                    team.remove_unit(it);
                }
            }
        }

    }

    LevelNS::CellType Game::getCellType(std::pair<int, int> pos) const {
        return CurrentLevel_.getCellType(pos);
    }

    void Game::setCellType(std::pair<int, int> pos, LevelNS::CellType new_type) {
        CurrentLevel_.setCellType(pos, new_type);
    }

    void Game::reload(int index) {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            auto ptr_item = ptr_oper->item_to_use(index);
            if (ptr_item->GetType() == ItemNS::CONTAINER) {
                auto container = dynamic_cast<RoundNS::RoundContainer *>(ptr_item);
                ptr_oper->reload(*container);
            } else {
                throw std::invalid_argument("No container under given index.");
            }
        } else {
            throw std::invalid_argument("This type entity unable to reload.");
        }
    }

    void Game::use_aid(int index) {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE || (*ActivePlayer_)->getType() == EntityNS::FORAGER) {
            ItemNS::Item *ptr_item = nullptr;
            if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
                auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
                ptr_item = ptr_oper->item_to_use(index);
            } else {
                auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
                ptr_item = ptr_foo->item_to_use(index);
            }
            if (ptr_item->GetType() == ItemNS::AID_KIT) {
                auto aid = dynamic_cast<FirstAidKitNS::FirstAidKit *>(ptr_item);
                if (aid->getUsageTime() > (*ActivePlayer_)->getCurTime()) {
                    throw std::runtime_error("Too little time to perform the operation.");
                }
                (*ActivePlayer_)->setCurHeatPoint(
                        std::min((*ActivePlayer_)->getCurHeatPoint() + aid->getHeatPointBoost(),
                                 (*ActivePlayer_)->getMaxHeatPoint()));
                (*ActivePlayer_)->setCurTime((*ActivePlayer_)->getCurTime() - aid->getUsageTime());

            } else {
                throw std::invalid_argument("No aid under given index.");
            }
        } else {
            throw std::invalid_argument("This type entity unable to use aid.");
        }
    }

    void Game::take_item(int index, InventoryNS::Inventory *inventory) {
        if ((*ActivePlayer_)->getType() != EntityNS::WILD_CREATURE) {
            if ((*ActivePlayer_)->getType() == EntityNS::INTELLIGENT_CREATURE) {
                auto ptr_wild = dynamic_cast<EntityNS::IntelligentCreature *>((*ActivePlayer_).get());
                ptr_wild->take_item(*inventory, index);
            } else if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
                auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
                ptr_oper->take_item(*inventory, index);
            } else if ((*ActivePlayer_)->getType() == EntityNS::FORAGER) {
                auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
                ptr_foo->take_item(*inventory, index);
            }
        } else {
            throw std::invalid_argument("This type entity unable to take items.");
        }
    }

    void Game::take_item_ground(int index) {
        take_item(index, CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()));
    }

    void Game::take_item_container(int index) {
        if (getCellType((*ActivePlayer_)->getPos()) != LevelNS::CONTAINER)
            throw std::runtime_error("Bad cell type: it's not container");
        take_item(index, CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()));
    }

    void Game::throw_item_ground(int index) {

        throw_item(CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()), index);
    }

    void Game::throw_item(InventoryNS::Inventory *inventory, int index) {
        std::unique_ptr<ItemNS::Item> item;
        if ((*ActivePlayer_)->getType() != EntityNS::WILD_CREATURE) {
            if ((*ActivePlayer_)->getType() == EntityNS::INTELLIGENT_CREATURE) {
                auto ptr_wild = dynamic_cast<EntityNS::IntelligentCreature *>((*ActivePlayer_).get());
                item = ptr_wild->throw_weapon();
            } else if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
                auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
                item = ptr_oper->throw_item(index);
            } else if ((*ActivePlayer_)->getType() == EntityNS::FORAGER) {
                auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
                item = ptr_foo->throw_item(index);
            }
            inventory->push_back(std::move(item));
        } else {
            throw std::invalid_argument("This type entity unable to throw items.");
        }
    }

    void Game::throw_item_container(int index) {
        if (getCellType((*ActivePlayer_)->getPos()) != LevelNS::CONTAINER)
            throw std::runtime_error("Bad cell type: it's not container");
        throw_item(CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()), index);
    }

    void Game::throw_all(InventoryNS::Inventory *inventory) {
        if ((*ActivePlayer_)->getType() == EntityNS::FORAGER) {
            auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
            ptr_foo->drop_all(*inventory);
        } else {
            throw std::invalid_argument("This type entity unable to throw all items.");
        }
    }

//    void Game::throw_all_items_ground() {
//        throw_all(CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()));
//    }

//    void Game::throw_item_container() {
//        throw_all(CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()));
//    }

    void Game::change_weapon(int index) {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            ptr_oper->change_weapon(index);
        } else {
            throw std::invalid_argument("This type entity unable to change weapon.");
        }
    }


    std::vector<std::shared_ptr<EntityNS::Entity>>
    Game::find_enemy(std::vector<std::pair<int, int>> &visiably_cells) const {
        return CurrentLevel_.find_enemy((*ActivePlayer_), (*ActiveTeam_), visiably_cells);
    }

    std::vector<std::pair<int, int>> Game::getVisibleCells() const {
        std::vector<std::pair<int, int>> result;
        for (auto &unit: *ActiveTeam_) {
            auto cells = CurrentLevel_.getVisibleCells(unit->getPos(), unit->getVisibilityRadius());
            result.insert(result.end(), cells.begin(), cells.end());
        }
        if ((*ActivePlayer_)->getType() == EntityNS::FORAGER ||
            (*ActivePlayer_)->getType() == EntityNS::INTELLIGENT_CREATURE) {
            auto containers = CurrentLevel_.find_container();
            result.insert(result.end(), containers.begin(), containers.end());
        }
        return result;
//        CurrentLevel_.getVisibleCells((*ActivePlayer_)->getPos(), (*ActivePlayer_)->getVisibilityRadius());
    }

    const EntityNS::EntityType Game::getPlayerType() const {
        return (*ActivePlayer_)->getType();
    }

    std::vector<const ItemNS::Item *> Game::show_items(const InventoryNS::Inventory &inventory) {
        return inventory.show_items();
    }

    std::vector<const ItemNS::Item *> Game::show_items_ground() const {
        return CurrentLevel_.show_items_ground((*ActivePlayer_)->getPos());
//        return show_items(*CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()));
    }

    std::vector<const ItemNS::Item *> Game::show_items_container() const {
        if (getCellType((*ActivePlayer_)->getPos()) != LevelNS::CONTAINER)
            throw std::runtime_error("Bad cell type: it's not container");
        //return show_items(*CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()));
        return CurrentLevel_.show_items_container((*ActivePlayer_)->getPos());
    }

    std::vector<const ItemNS::Item *> Game::show_items_player() const {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            return ptr_oper->show_inventory();
        } else if ((*ActivePlayer_)->getType() == EntityNS::FORAGER) {
            auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
            return ptr_foo->show_inventory();
        } else if ((*ActivePlayer_)->getType() == EntityNS::INTELLIGENT_CREATURE) {
            auto ptr_intell = dynamic_cast<EntityNS::IntelligentCreature *>((*ActivePlayer_).get());
            auto weapon = ptr_intell->getActiveWeapon();
            std::vector<const ItemNS::Item *> result;
            if (weapon) {
                result.push_back(weapon);
            }
            return result;
        } else {
            throw std::invalid_argument("This entity has no inventory");
        }
    }


    std::pair<int, int> Game::getActivePlayerCoord() const {
        return (*ActivePlayer_)->getPos();
    }

    void Game::move_direction(Game::MoveDirectionType &direction) {
        auto [i, j] = (*ActivePlayer_)->getPos();
        switch (direction) {

            case DOWN:
                move({i + 1, j});
                break;
            case UP:
                move({i - 1, j});
                break;
            case RIGHT:
                move({i, j + 1});
                break;
            case LEFT:
                move({i, j - 1});
                break;
        }
    }

    LevelNS::CellType Game::getMyCell() const {
        return getCellType(getActivePlayerCoord());
    }

    std::pair<int, int> Game::getActivePlayerHealth() const {
        auto cur = (*ActivePlayer_)->getCurHeatPoint();
        auto max = (*ActivePlayer_)->getMaxHeatPoint();
        return {cur, max};
    }

    std::pair<int, int> Game::getActivePlayerTime() const {
        auto cur = (*ActivePlayer_)->getCurTime();
        auto max = (*ActivePlayer_)->getAvaliableTime();
        return {cur, max};
    }

    std::string Game::getActivePlayerDesc() const {
        return (*ActivePlayer_)->toString();
    }

    void Game::use(int index) {
        auto unit = *ActivePlayer_;
        if (unit->getType() == EntityNS::OPERATIVE || unit->getType() == EntityNS::FORAGER) {
            ItemNS::Item *ptr_item = nullptr;
            if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
                auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
                ptr_item = ptr_oper->item_to_use(index);
            } else {
                auto ptr_foo = dynamic_cast<EntityNS::Forager *>((*ActivePlayer_).get());
                ptr_item = ptr_foo->item_to_use(index);
            }
            switch (ptr_item->GetType()) {

                case ItemNS::WEAPON:
                    change_weapon(index);
                    break;
                case ItemNS::AID_KIT:
                    use_aid(index);
                    break;
                case ItemNS::CONTAINER:
                    reload(index);
                    break;
            }
        } else {
            throw std::runtime_error("This type of entity unable to use items");
        }
    }

    void Game::prev_player() {
        if (ActivePlayer_ == ActiveTeam_->begin()) {
            ActivePlayer_ = ActiveTeam_->end();
        }
        --ActivePlayer_;
    }

    std::vector<std::pair<std::pair<int, int>, EntityNS::EntityType>> Game::getTeammates() const {
        std::vector<std::pair<std::pair<int, int>, EntityNS::EntityType>> result;
        for (auto &unit: *ActiveTeam_) {
            if (unit != *ActivePlayer_) {
                result.emplace_back(unit->getPos(), unit->getType());
            }
        }
        return result;
    }

    bool Game::checkGameOver() {
        for (auto it = Teams_.begin(); it != Teams_.end(); it++) {
            if (it != ActiveTeam_) {
                if ((*it).getSize() != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void Game::attack(std::shared_ptr<EntityNS::Entity> &enemy) {
        this->shot(enemy->getPos(), enemy);
    }


} // GameNS