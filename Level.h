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
        //TODO
        // 6. Итератор по инвентарям команд
        void place_unit(std::pair<int, int> pos, std::unique_ptr<EntityNS::Entity>);
        void move_unit(std::pair<int, int> pos, std::unique_ptr<EntityNS::Entity>);
        void remove_unit(std::pair<int, int> pos, int index);
        void place_item(std::pair<int, int> pos, std::unique_ptr<ItemNS::Item>);
        void remove_item(std::pair<int, int> pos, int index);

        void setCellType(std::pair<int, int> pos, CellType type);
        void resize(int new_x, int new_y);

        // Тут, наверное, shared_ptr?
        std::vector<std::shared_ptr<EntityNS::Entity>> find_enemy(TeamNS::Team& my_team);
        std::vector<std::pair<int, int>> find_container();
        friend class Cell;
    private:
        std::vector<std::shared_ptr<TeamNS::Team>> Teams_;
        std::shared_ptr<Matrix<Cell>> Board_;
    };

} // LevelNS

#endif //LAB3_LEVEL_H
