//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_TEAM_H
#define LAB3_TEAM_H
#include "Entity.h"
namespace TeamNS {

    class Team {
    private:
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // TeamNS

#endif //LAB3_TEAM_H
