//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_CELL_H
#define LAB3_CELL_H
#include "Inventory.h"
#include "Entity.h"
namespace CellNS {

    class Cell {
    public:
        //TODO:
        // 1. Определить производные классы
        // 2. Virtual destructor
        // 3. Метод: добавить предмет
        // 4. Удалить предмет
        // 5. Список предметов - инвентарь
        virtual ~Cell() = default;
    private:
        InventoryNS::Inventory ItemsGround_;
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // CellNS

#endif //LAB3_CELL_H
