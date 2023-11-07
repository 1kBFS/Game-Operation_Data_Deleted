//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_FIRSTAIDKIT_H
#define LAB3_FIRSTAIDKIT_H

#include "Item.h"

namespace FirstAidKitNS {

    class FirstAidKit : public ItemNS::Item {
    public:
        FirstAidKit(const std::string &title, int weight=1, int usageTime=1, int heatPointBoost=25);

        int getUsageTime() const;

        void setUsageTime(int usageTime);

        int getHeatPointBoost() const;

        void setHeatPointBoost(int heatPointBoost);

        ItemNS::ItemType GetType() const override;

    private:
        int UsageTime_;
        int HeatPointBoost_;
    };

} // FirstAidKitNS

#endif //LAB3_FIRSTAIDKIT_H
