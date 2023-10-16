//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_ROUNDCONTAINER_H
#define LAB3_ROUNDCONTAINER_H
#include "Item.h"
namespace RoundNS {

    class RoundContainer: public ItemNS::Item {
    public:
        RoundContainer(const std::string &title, int weight, int roundType, int capacity, int size);

        int getRoundType() const;

        int getCapacity() const;

        int getSize() const;

        void setRoundType(int roundType);

        void setCapacity(int capacity);

        void setSize(int size);

        void extract(int amount);

        ItemNS::ItemType GetType() const override;

    private:
        int RoundType_;
        int Capacity_;
        int Size_;
    };

} // RoundNS

#endif //LAB3_ROUNDCONTAINER_H
