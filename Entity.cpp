//
// Created by Pavel on 15.10.2023.
//

#include "Entity.h"

namespace EntityNS {
    Entity::Entity(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime,
                   int stepTime, int visibilityRadius) : Name_(name), maxHeatPoint_(maxHeatPoint),
                                                         curHeatPoint_(curHeatPoint), curTime_(curTime),
                                                         AvaliableTime_(avaliableTime), StepTime_(stepTime),
                                                         VisibilityRadius_(visibilityRadius) {}

    const std::string &Entity::getName() const {
        return Name_;
    }

    void Entity::setName(const std::string &name) {
        Name_ = name;
    }

    int Entity::getMaxHeatPoint() const {
        return maxHeatPoint_;
    }

    void Entity::setMaxHeatPoint(int maxHeatPoint) {
        maxHeatPoint_ = maxHeatPoint;
    }

    int Entity::getCurHeatPoint() const {
        return curHeatPoint_;
    }

    void Entity::setCurHeatPoint(int curHeatPoint) {
        curHeatPoint_ = curHeatPoint;
    }

    int Entity::getCurTime() const {
        return curTime_;
    }

    void Entity::setCurTime(int curTime) {
        curTime_ = curTime;
    }

    int Entity::getAvaliableTime() const {
        return AvaliableTime_;
    }

    void Entity::setAvaliableTime(int avaliableTime) {
        AvaliableTime_ = avaliableTime;
    }

    int Entity::getStepTime() const {
        return StepTime_;
    }

    void Entity::setStepTime(int stepTime) {
        StepTime_ = stepTime;
    }

    int Entity::getVisibilityRadius() const {
        return VisibilityRadius_;
    }

    void Entity::setVisibilityRadius(int visibilityRadius) {
        VisibilityRadius_ = visibilityRadius;
    }

    std::vector<std::unique_ptr<Entity>> Entity::find_enemy() {

        return std::vector<std::unique_ptr<Entity>>();
    }
} // EntityNS