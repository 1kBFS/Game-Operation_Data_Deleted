//
// Created by Pavel on 15.10.2023.
//

#include "Team.h"

#include <utility>

namespace TeamNS {


    int Team::getSize() const {
        return static_cast<int>(Entities_.size());
    }

    Team::TeamIterator Team::begin() {
        return Entities_.begin();
    }

    Team::TeamIterator Team::end() {
        return Entities_.end();
    }

    Team::const_TeamIterator Team::begin() const {
        return Entities_.begin();
    }

    Team::const_TeamIterator Team::end() const {
        return Entities_.end();
    }

    void Team::push_back(std::shared_ptr<EntityNS::Entity>&& new_entity) {
        Entities_.push_back(std::move(new_entity));
    }

    void Team::remove_unit(TeamIterator pos) {
        Entities_.erase(pos);
    }

    Team::Team(std::string title) : Title_(std::move(title)) {}

    Team::TeamIterator Team::find(const std::shared_ptr<EntityNS::Entity> &entity_to_find) {
        return std::find(Entities_.begin(), Entities_.end(), entity_to_find);
    }


} // TeamNS