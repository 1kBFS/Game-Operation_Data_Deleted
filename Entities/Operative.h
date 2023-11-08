//
// Created by Master on 17.10.2023.
//

#ifndef LAB3_OPERATIVE_H
#define LAB3_OPERATIVE_H

#include <memory>
#include <optional>

#include "Entity.h"
#include "../Items/Inventory.h"
#include "../Items/Weapon.h"
namespace EntityNS{

class Operative : public EntityNS::Entity {
public:


    explicit Operative(const std::string &name, int maxHeatPoint=100, int curHeatPoint=100, int curTime=100, int avaliableTime=100, int stepTime=1,
              int visibilityRadius=1, int reloadTime=2, int maxWeight=15, int accuracy=100);

    void change_weapon(int index);

    void take_item(InventoryNS::Inventory &inventory, int index);

    void put_item(std::unique_ptr<ItemNS::Item>&& new_item);
    std::unique_ptr<ItemNS::Item> throw_item(int index);

    void reload(RoundNS::RoundContainer &container);
    /**
    * \brief Выстрелить по врагу
    * \param enemy Ссылка на объект EntityNS::Entity, представляющий врага
    * \return true, если выстрел успешен, false, если нет
    * \throw std::runtime_error, если нет активного оружия или слишком мало времени для выполнения операции
    * \details Функция пытается выстрелить по врагу с помощью активного оружия, учитывая вероятность попадания и время выстрела.
    * Если выстрел успешен, то уменьшает здоровье врага на значение, возвращаемое функцией shot активного оружия.
    * Если выстрел неудачен, то ничего не делает. В любом случае уменьшает текущее время на значение, возвращаемое функцией getShotTime активного оружия.
    */
    bool shot(EntityNS::Entity &enemy);

    [[nodiscard]] EntityType getType() const override;

    void move(int new_i, int new_j) override;

    std::optional<InventoryNS::Inventory> die() override;

    [[nodiscard]] int getReloadTime() const;

    void setReloadTime(int reloadTime);

    [[nodiscard]] int getMaxWeight() const;

    void setMaxWeight(int maxWeight);

    [[nodiscard]] int getAccuracy() const;

    void setAccuracy(int accuracy);

    void setInvetnory(InventoryNS::Inventory &&invetnory);

    void setActiveWeapon(WeaponNS::Weapon& weapon);

    [[nodiscard]] std::string getActiveWeaponTitle() const;

    [[nodiscard]] int getCurrentWeight() const;

private:

    std::unique_ptr<WeaponNS::Weapon> ActiveWeapon_;
    InventoryNS::Inventory Inventory_;
    int ReloadTime_ = 2;
    int maxWeight_ = 15;
    int Accuracy_ = 100; // 1...100

};
}

#endif //LAB3_OPERATIVE_H
