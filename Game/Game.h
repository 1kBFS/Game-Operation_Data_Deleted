//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include "../Level/Team.h"
#include "../Level/Level.h"
#include <map>

namespace GameNS {

    class Game {
        Game(int size, std::vector<TeamNS::Team> &&teams);

        void reset_time();

        void next_player();

        void next_team();

        void move(std::pair<int, int> new_pos);

        void shot(std::pair<int, int> attack_pos, std::shared_ptr<EntityNS::Entity> &enemy);

        void reload(int index);

        void use_aid(int index);

        std::unique_ptr<ItemNS::Item> take_item_ground(std::pair<int, int> pos, int index);

        std::unique_ptr<ItemNS::Item> take_item_container(std::pair<int, int> pos, int index);

        LevelNS::CellType getCellType(std::pair<int, int> pos);

        void setCellType(std::pair<int, int> pos, LevelNS::CellType new_type);

    private:
        TeamNS::Team::TeamIterator ActivePlayer_;
        std::vector<TeamNS::Team>::iterator ActiveTeam_;
        LevelNS::Level CurrentLevel_;
        std::vector<TeamNS::Team> Teams_;

        std::map<std::weak_ptr<EntityNS::Entity>, TeamNS::Team &> which_team;
    };

} // GameNS

#endif //LAB3_GAME_H
