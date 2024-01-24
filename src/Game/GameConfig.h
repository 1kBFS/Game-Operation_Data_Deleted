//
// Created by Pavel on 25.12.2023.
//

#ifndef LAB3_GAMECONFIG_H
#define LAB3_GAMECONFIG_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Game.h"
#include "../Entities/Operative.h"
#include "../Entities/Wild_Creature.h"
#include "../Items/FirstAidKit.h"
#include  "../Entities/Forager.h"
#include "../Entities/Intelligent_Creature.h"

using json = nlohmann::json;
namespace GameNS {

    class GameConfig {
    public:
        Game configure_game(const std::string &filename);

    private:
        std::vector<TeamNS::Team> form_team(json &data);

        static std::unique_ptr<FirstAidKitNS::FirstAidKit> form_aid(json &element);

        static std::unique_ptr<WeaponNS::Weapon> form_weapon(json &element);

        static std::unique_ptr<RoundNS::RoundContainer> form_ammo_container(json &element);

        std::shared_ptr<EntityNS::Operative> form_operative(json &element);

        std::shared_ptr<EntityNS::WildCreature> form_wild(json &element);

        std::shared_ptr<EntityNS::Forager> form_forager(json &element);

        std::shared_ptr<EntityNS::IntelligentCreature> form_intelligent(json &element);


    };
} // GameNS


#endif //LAB3_GAMECONFIG_H
