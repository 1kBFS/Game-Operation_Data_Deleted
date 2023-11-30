//
// Created by Master on 12.10.2023.
//

#ifndef LAB3_ROUNDCONTAINER_H
#define LAB3_ROUNDCONTAINER_H
#include "Item.h"
namespace RoundNS {
    /*!
	\brief Контейнер с патронами. Наследник Item.
    */
    class RoundContainer: public ItemNS::Item {
    public:
        /*!
         * @brief Конструктор для контейнера с патронами.
         * @param title название контейнера
         * @param roundType тип хранимых патронов
         * @param size текущее количество патронов в контейнере
         * @param weight вес контейнера
         * @param capacity вместимость
         */
        explicit RoundContainer(const std::string &title, int roundType, int size=10, int weight=5, int capacity=10);

        [[nodiscard]] int getRoundType() const;

        [[nodiscard]] int getCapacity() const;

        [[nodiscard]] int getSize() const;

        void setRoundType(int roundType);

        void setCapacity(int capacity);

        void setSize(int size);
        /*!
         * @brief Извлечь патроны из контейнера.
         * @param amount требуемое число патронов
         * @throws std::invalid_argument amount <= 0
         * @throws std::runtime_error  контейнер пуст
         * @return извлеченное число патронов
         *
         * @details Size уменьшается на min(amount, Size_)
         */
        int extract(int amount);

        [[nodiscard]] ItemNS::ItemType GetType() const override;

    private:
        int RoundType_;
        int Capacity_;
        int Size_;
    };

} // RoundNS

#endif //LAB3_ROUNDCONTAINER_H
