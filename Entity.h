//
// Created by Pavel on 15.10.2023.
//

#ifndef LAB3_ENTITY_H
#define LAB3_ENTITY_H

#include <string>
#include <vector>
#include <memory>
// TODO: описать производные классы
namespace EntityNS {

    enum EntityType {
        OPERATIVE, WILD_CREATURE, INTELLIGENT_CREATURE, FORAGER
    };

    class Entity {
    public:
        Entity(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime,
               int stepTime, int visibilityRadius);

        virtual EntityType getType() const = 0;

        virtual void move(int new_i, int new_j) = 0;

        virtual void die() = 0;

        // Тут наверное shared_ptr

        const std::string &getName() const;

        void setName(const std::string &name);

        int getMaxHeatPoint() const;

        void setMaxHeatPoint(int maxHeatPoint);

        int getCurHeatPoint() const;

        void setCurHeatPoint(int curHeatPoint);

        int getCurTime() const;

        void setCurTime(int curTime);

        int getAvaliableTime() const;

        void setAvaliableTime(int avaliableTime);

        int getStepTime() const;

        void setStepTime(int stepTime);

        int getVisibilityRadius() const;

        void setVisibilityRadius(int visibilityRadius);

        virtual ~Entity()= default;

    private:
        // TODO: добавить указатель на Team
        int i, j;
        // std::shared_ptr<Matrix<CellNS::Cell>> Board_;
        std::string Name_;
        int maxHeatPoint_;
        int curHeatPoint_;
        int curTime_;
        int AvaliableTime_;
        int StepTime_;
        int VisibilityRadius_;
    };


} // EntityNS

#endif //LAB3_ENTITY_H
