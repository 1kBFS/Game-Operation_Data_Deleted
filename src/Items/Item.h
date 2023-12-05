//
// Created by Pavel on 11.10.2023.
//

#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

#include <string>
#include <iostream>
#include <utility>

namespace ItemNS {

    enum ItemType {
        WEAPON, AID_KIT, CONTAINER
    };

    /*!
	\brief Базовый класс для предметов
    */
    class Item {
    public:
        /*!
	    @brief Конструктор класса Item.
	    @param title - название предмета
        @param weight - вес предмета
	    @throws std::invalid_argument в случае отрицательного веса
        */
        Item(std::string title, int weight);

        [[nodiscard]] const std::string &GetTitle() const {
            return Title_;
        }

        [[nodiscard]] int getWeight() const;

        [[nodiscard]] virtual ItemType GetType() const = 0;

        [[nodiscard]] virtual std::string toString() const = 0;

        virtual ~Item() = default;

    private:
        std::string Title_;
        int Weight_;
    };


} // ItemNS

#endif //LAB3_ITEM_H
