//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_LEVEL_H
#define LAB3_LEVEL_H

#include <vector>
#include <memory>
#include "Team.h"
#include "Matrix.h"
#include "Cell.h"
#include "Entity.h"

namespace LevelNS {

    class Level {
        //TODO:
        // 1. Функции из задания
        // 2. Добавление юнитов в команду
        // 3. Добавление юнтиов на поле
        // 4. Добавление предметов на поле
        // 5. Resize, Getters
        // 6. Итератор по инвентарям команд
        // 7. Check if two creatures in one team

        // Тут, наверное, shared_ptr?
        std::vector<std::shared_ptr<EntityNS::Entity>> find_enemy(TeamNS::Team& my_team);

    private:
        std::vector<std::shared_ptr<TeamNS::Team>> Teams_;
        std::shared_ptr<Matrix<CellNS::Cell>> Board_;
    };

} // LevelNS

#endif //LAB3_LEVEL_H
