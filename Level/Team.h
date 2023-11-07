//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_TEAM_H
#define LAB3_TEAM_H

#include "../Entities/Entity.h"
#include "../Items/Inventory.h"

namespace TeamNS {
    template<typename T>
    class TeamInventoryIterator : public std::iterator<std::input_iterator_tag, T> {
        friend class Team;

    private:
        TeamInventoryIterator(std::vector<std::unique_ptr<ItemNS::Item>>::iterator item,
                              std::vector<std::shared_ptr<EntityNS::Entity>>::iterator entity);

    public:
        TeamInventoryIterator(const TeamInventoryIterator &it);

        bool operator!=(TeamInventoryIterator const &other) const;

        typename TeamInventoryIterator::reference operator*() const;

        TeamInventoryIterator &operator++();

    private:
        std::vector<std::shared_ptr<EntityNS::Entity>>::iterator currentEntityIterator_;
        std::vector<std::unique_ptr<ItemNS::Item>>::iterator currentInvetoryIterator_;
    };

    class Team {
        typedef TeamInventoryIterator<std::unique_ptr<ItemNS::Item>> iterator;

        void add_unit(int pos);

        void remove_unit(int pos);

        void push_back(int pos);

        int getSize() const;
        iterator begin();

        iterator end();

    private:
        std::vector<std::shared_ptr<EntityNS::Entity>> Entities_;
    };

} // TeamNS

#endif //LAB3_TEAM_H
