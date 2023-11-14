//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <optional>

#include "../Items/Inventory.h"

namespace EntityNS {

    enum EntityType {
        OPERATIVE, WILD_CREATURE, INTELLIGENT_CREATURE, FORAGER
    };

    class Entity {
    public:
        Entity(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime,
               int stepTime, int visibilityRadius);

        explicit Entity(std::string name) : Name_(std::move(name)) {}

        [[nodiscard]] virtual EntityType getType() const = 0;

        virtual void move(int new_i, int new_j) = 0;

        virtual std::optional<InventoryNS::Inventory> die() = 0;

        [[nodiscard]] const std::string &getName() const;

        void setName(const std::string &name);

        [[nodiscard]] int getMaxHeatPoint() const;

        void setMaxHeatPoint(int maxHeatPoint);

        [[nodiscard]] int getCurHeatPoint() const;

        void setCurHeatPoint(int curHeatPoint);

        [[nodiscard]] int getCurTime() const;

        void setCurTime(int curTime);

        [[nodiscard]] int getAvaliableTime() const;

        void setAvaliableTime(int avaliableTime);

        [[nodiscard]] int getStepTime() const;

        void setStepTime(int stepTime);

        [[nodiscard]] int getVisibilityRadius() const;

        void setVisibilityRadius(int visibilityRadius);

        [[nodiscard]] std::pair<int, int> getPos() const;

        void setPos(std::pair<int, int> pos);

        void reset_time();

        void decrease_hp(int amount);

        virtual ~Entity() = default;

    protected:

        int i = 0, j = 0;
        std::string Name_;
        int maxHeatPoint_ = 100;
        int curTime_ = 0;
        int AvaliableTime_ = 0;
        int StepTime_ = 1;
        int VisibilityRadius_ = 5;
        int curHeatPoint_ = 100;
    };


} // EntityNS

#endif //LAB3_ENTITY_H
