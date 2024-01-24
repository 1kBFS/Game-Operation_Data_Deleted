//
// Created by Pavel on 25.12.2023.
//

#include "GameConfig.h"
#include "../Entities/Operative.h"

namespace GameNS {
    Game GameConfig::configure_game(const std::string &filename) {
        std::ifstream f(filename);
        if (f.fail()) {
            throw std::runtime_error("No such config file");
        }
        json data = json::parse(f);
        Game game;
        game.CurrentLevel_.resize(data["width"], data["height"]);
        game.Teams_ = form_team(data);
        game.ActiveTeam_ = game.Teams_.begin();
        game.ActivePlayer_ = game.ActiveTeam_->begin();
        for (auto &team: game.Teams_) {
            for (auto &unit: team) {
                game.CurrentLevel_.place_unit(unit->getPos(), unit);
            }
        }
        return game;
    }

    std::vector<TeamNS::Team> GameConfig::form_team(json &data) {
        int teams_amount = data["teams_amount"];
        std::vector<TeamNS::Team> teams(teams_amount);
        for (json &element: data["Operatives"]) {
            teams[element["team_number"]].push_back(std::move(form_operative(element)));
        }
        for (json &element: data["Wilds"]) {
            teams[element["team_number"]].push_back(std::move(form_wild(element)));
        }
        for (json &element: data["Foragers"]) {
            teams[element["team_number"]].push_back(std::move(form_forager(element)));
        }
        for (json &element: data["Intelligence"]) {
            teams[element["team_number"]].push_back(std::move(form_intelligent(element)));
        }
        return teams;
    }


    std::shared_ptr<EntityNS::Operative> GameConfig::form_operative(json &element) {
        auto operative_unit = std::make_shared<EntityNS::Operative>(element["Name"], element["MaxHeatPoint"],
                                                                    element["CurHeatPoint"], element["CurTime"],
                                                                    element["AvaliableTime"], element["StepTime"],
                                                                    element["VisibilityRadius"],
                                                                    element["ReloadTime"],
                                                                    element["MaxWeight"], element["Accuracy"]);
        operative_unit->setPos({element["i"], element["j"]});
        InventoryNS::Inventory loaded_inventory_unit;
        for (json &item: element["Inventory"]["Aids"]) {
            loaded_inventory_unit.push_back(std::move(form_aid(item)));
        }
        for (json &item: element["Inventory"]["Containers"]) {
            loaded_inventory_unit.push_back(std::move(form_ammo_container(item)));
        }
        for (json &item: element["Inventory"]["Weapons"]) {
            loaded_inventory_unit.push_back(std::move(form_weapon(item)));
        }
        operative_unit->setActiveWeapon(*form_weapon(element["ActiveWeapon"]));
        operative_unit->setInvetnory(std::move(loaded_inventory_unit));
        return operative_unit;
    }

    std::unique_ptr<FirstAidKitNS::FirstAidKit> GameConfig::form_aid(json &element) {
        return std::make_unique<FirstAidKitNS::FirstAidKit>(element["Title"], element["Weight"],
                                                            element["UsageTime"], element["HeatPointBoost"]);
    }

    std::unique_ptr<RoundNS::RoundContainer> GameConfig::form_ammo_container(json &element) {
        return std::make_unique<RoundNS::RoundContainer>(element["Title"], element["RoundType"], element["Size"],
                                                         element["Weight"], element["Capacity"]);
    }

    std::unique_ptr<WeaponNS::Weapon> GameConfig::form_weapon(json &element) {
        auto ptr= std::make_unique<WeaponNS::Weapon>(element["Title"], element["RoundType"], element["Weight"],
                                                  element["MagazineSize"], element["Damage"], element["ShotTime"],
                                                  element["ReloadTime"], element["MagazineCapacity"]);
        return ptr;
    }

    std::shared_ptr<EntityNS::WildCreature> GameConfig::form_wild(json &element) {
        auto unit = std::make_shared<EntityNS::WildCreature>(element["Name"], element["Damage"], element["Accuracy"]);
        unit->setMaxHeatPoint(element["MaxHeatPoint"]);
        unit->setCurTime(element["CurTime"]);
        unit->setAvaliableTime(element["AvaliableTime"]);
        unit->setStepTime(element["StepTime"]);
        unit->setVisibilityRadius(element["VisibilityRadius"]);
        unit->setCurHeatPoint(element["CurHeatPoint"]);
        unit->setPos({element["i"], element["j"]});
        return unit;
    }

    std::shared_ptr<EntityNS::Forager> GameConfig::form_forager(json &element) {
        auto unit = std::make_shared<EntityNS::Forager>(element["Name"]);
        unit->setMaxHeatPoint(element["MaxHeatPoint"]);
        unit->setCurTime(element["CurTime"]);
        unit->setAvaliableTime(element["AvaliableTime"]);
        unit->setStepTime(element["StepTime"]);
        unit->setVisibilityRadius(element["VisibilityRadius"]);
        unit->setCurHeatPoint(element["CurHeatPoint"]);
        unit->setPos({element["i"], element["j"]});
        InventoryNS::Inventory loaded_inventory_unit;
        for (json &item: element["Inventory"]["Aids"]) {
            loaded_inventory_unit.push_back(std::move(form_aid(item)));
        }
        for (json &item: element["Inventory"]["Containers"]) {
            loaded_inventory_unit.push_back(std::move(form_ammo_container(item)));
        }
        for (json &item: element["Inventory"]["Weapons"]) {
            loaded_inventory_unit.push_back(std::move(form_weapon(item)));
        }
        unit->setInvetnory(std::move(loaded_inventory_unit));
        return unit;
    }

    std::shared_ptr<EntityNS::IntelligentCreature> GameConfig::form_intelligent(json &element) {
        auto unit = std::make_shared<EntityNS::IntelligentCreature>(element["Name"], element["Accuracy"]);
        unit->setMaxHeatPoint(element["MaxHeatPoint"]);
        unit->setCurTime(element["CurTime"]);
        unit->setAvaliableTime(element["AvaliableTime"]);
        unit->setStepTime(element["StepTime"]);
        unit->setVisibilityRadius(element["VisibilityRadius"]);
        unit->setCurHeatPoint(element["CurHeatPoint"]);
        unit->setPos({element["i"], element["j"]});
        unit->put_weapon(std::move(form_weapon(element["ActiveWeapon"])));
        return unit;
    }

} // GameNS