//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_ROUNDCONTAINER_H
#define LAB3_ROUNDCONTAINER_H
#include "Item.h"
namespace RoundNS {

    class RoundContainer: public ItemNS::Item {
    public:
        explicit RoundContainer(const std::string &title, int roundType, int size=10, int weight=5, int capacity=10);

        [[nodiscard]] int getRoundType() const;

        [[nodiscard]] int getCapacity() const;

        [[nodiscard]] int getSize() const;

        void setRoundType(int roundType);

        void setCapacity(int capacity);

        void setSize(int size);

        int extract(int amount);

        [[nodiscard]] ItemNS::ItemType GetType() const override;

    private:
        int RoundType_;
        int Capacity_;
        int Size_;
    };

} // RoundNS

#endif //LAB3_ROUNDCONTAINER_H
