//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_TEAM_H
#define LAB3_TEAM_H

#include "../Entities/Entity.h"
#include "../Items/Inventory.h"

namespace TeamNS {

    class Team {
    public:
        explicit Team(std::string title);

        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::iterator TeamIterator;
        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::const_iterator const_TeamIterator;

        void remove_unit(TeamIterator pos);
        void push_back(std::shared_ptr<EntityNS::Entity>& new_entity);
        [[nodiscard]] int getSize() const;

        TeamIterator begin();
        TeamIterator end();

        [[nodiscard]] const_TeamIterator begin() const;
        [[nodiscard]] const_TeamIterator end() const;

    private:
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
        std::string Title_;
    };

} // TeamNS

#endif //LAB3_TEAM_H
