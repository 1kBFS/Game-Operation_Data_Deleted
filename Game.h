//
// Created by Pavel on 18.10.2023.
//

#ifndef LAB3_GAME_H
#define LAB3_GAME_H
#include "Level/Team.h"
#include "Level/Level.h"
namespace GameNS {

    class Game {
        void load_game(std::istream& file);
        void reset_time();
        bool isRoundEnd();

        std::shared_ptr<EntityNS::Entity> choose_player(int index);
        void next_team();

    private:
        std::shared_ptr<TeamNS::Team> ActiveTeam_;
        LevelNS::Level CurrentLevel_;
    };

} // GameNS

#endif //LAB3_GAME_H
