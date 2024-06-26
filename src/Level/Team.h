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
        /*!
         * @brief Конструктор класса Team.
         * @param title название команды.
         */
        explicit Team(std::string title);
        Team() = default;
        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::iterator TeamIterator;
        typedef std::vector<std::shared_ptr<EntityNS::Entity>>::const_iterator const_TeamIterator;

        /*!
         * @brief Удалить юнита из команды
         * @param pos итератор на позицию
         */
        void remove_unit(TeamIterator pos);

        /*!
         * @brief Переместить юнита в конец команды.
         * @param new_entity юнит для добавления.
         */
        void push_back(std::shared_ptr<EntityNS::Entity> &&new_entity);

        /*!
         * @brief Найти юнита.
         * @param entity_to_find юнит для поиска.
         * @return итератор на позицию.
         */
        TeamIterator find(const std::shared_ptr<EntityNS::Entity> &entity_to_find);

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
