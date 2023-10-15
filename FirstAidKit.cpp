//
// Created by Master on 12.10.2023.
//

#include "FirstAidKit.h"

namespace FirstAidKitNS {

    FirstAidKit::FirstAidKit(const std::string &title, int weight, int usageTime, int heatPointBoost) : Item(title,
                                                                                                             weight),
                                                                                                        UsageTime_(
                                                                                                                usageTime),
                                                                                                        HeatPointBoost_(
                                                                                                                heatPointBoost) {}

    int FirstAidKit::getUsageTime() const {
        return UsageTime_;
    }

    void FirstAidKit::setUsageTime(int usageTime) {
        UsageTime_ = usageTime;
    }

    int FirstAidKit::getHeatPointBoost() const {
        return HeatPointBoost_;
    }

    void FirstAidKit::setHeatPointBoost(int heatPointBoost) {
        HeatPointBoost_ = heatPointBoost;
    }
} // FirstAidKitNS