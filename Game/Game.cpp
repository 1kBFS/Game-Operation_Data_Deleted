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

    void Game::next_team() {
        ActiveTeam_++;
        if (ActiveTeam_ == Teams_.end()) {
            ActiveTeam_ = Teams_.begin();
        }
    }

    void Game::move(std::pair<int, int> new_pos) {
        CurrentLevel_.move_unit(new_pos, *ActivePlayer_);
    }

    void Game::shot(std::pair<int, int> attack_pos, std::shared_ptr<EntityNS::Entity> &enemy) {
        auto cells_on_line = LevelNS::Level::getCellsOnLine((*ActivePlayer_)->getPos(), enemy->getPos());
        if (!CurrentLevel_.check_all(cells_on_line, LevelNS::Cell::isVisiable)) {
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
        }
        if (enemy->getCurHeatPoint() < 0) {
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

    LevelNS::CellType Game::getCellType(std::pair<int, int> pos) {
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
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            auto ptr_item = ptr_oper->item_to_use(index);
            if (ptr_item->GetType() == ItemNS::AID_KIT) {
                auto aid = dynamic_cast<FirstAidKitNS::FirstAidKit *>(ptr_item);
                if (aid->getUsageTime() > (*ActivePlayer_)->getCurTime()) {
                    throw std::runtime_error("Too little time to perform the operation.");
                }
                (*ActivePlayer_)->setCurHeatPoint(
                        std::min((*ActivePlayer_)->getCurHeatPoint() + aid->getHeatPointBoost(),
                                 (*ActivePlayer_)->getMaxHeatPoint()));

            } else {
                throw std::invalid_argument("No container under given index.");
            }
        } else {
            throw std::invalid_argument("This type entity unable to reload.");
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
                ptr_foo->throw_item(index);
            }
            inventory->push_back(std::move(item));
        } else {
            throw std::invalid_argument("This type entity unable to throw items.");
        }
    }

    void Game::throw_item_container(int index) {
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

    void Game::throw_all_items_ground() {
        throw_all(CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()));
    }

    void Game::throw_item_container() {
        throw_all(CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()));
    }

    void Game::change_weapon(int index) {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {
            auto ptr_oper = dynamic_cast<EntityNS::Operative *>((*ActivePlayer_).get());
            ptr_oper->change_weapon(index);
        } else {
            throw std::invalid_argument("This type entity unable to throw all items.");
        }
    }

    std::vector<std::pair<int, int>> Game::find_containers() {
        return CurrentLevel_.find_container();
    }

    std::vector<std::shared_ptr<EntityNS::Entity>> Game::find_enemy(std::vector<std::pair<int, int>> &visiably_cells) {
        return CurrentLevel_.find_enemy((*ActivePlayer_), (*ActiveTeam_), visiably_cells);
    }

    std::vector<std::pair<int, int>> Game::update_visibility() {
        return CurrentLevel_.getVisibleCells((*ActivePlayer_)->getPos(), (*ActivePlayer_)->getVisibilityRadius());
    }

    EntityNS::EntityType Game::getPlayerType() {
        return (*ActivePlayer_)->getType();
    }

    std::vector<ItemNS::Item *> Game::show_items(InventoryNS::Inventory &inventory) {
        return inventory.show_items();
    }

    std::vector<ItemNS::Item *> Game::show_items_ground() {
        return show_items(*CurrentLevel_.get_inventory_ground((*ActivePlayer_)->getPos()));
    }

    std::vector<ItemNS::Item *> Game::show_items_container() {
        return show_items(*CurrentLevel_.get_inventory_container((*ActivePlayer_)->getPos()));
    }

    std::vector<ItemNS::Item *> Game::show_items_player() {
        if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {

        } else if ((*ActivePlayer_)->getType() == EntityNS::OPERATIVE) {

        } else {
            throw std::invalid_argument("This entity has no inventory");
        }
    }


} // GameNS