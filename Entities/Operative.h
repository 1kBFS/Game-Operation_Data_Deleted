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

class Operative : EntityNS::Entity {
public:
    Operative(const std::string &name, int maxHeatPoint, int curHeatPoint, int curTime, int avaliableTime, int stepTime,
              int visibilityRadius, int reloadTime, int maxWeight, int accuracy,
              const InventoryNS::Inventory &inventory, const std::optional<WeaponNS::Weapon> &activeWeapon);

    void change_weapon(int index);

    void take_item(InventoryNS::Inventory &inventory, int index);

    std::unique_ptr<ItemNS::Item> throw_item(int index);

    int getCurrentWeight();

    void reload(const RoundNS::RoundContainer &container);

    void shot(EntityNS::Entity &enemy);

    EntityType getType() const override;

    void move(int new_i, int new_j) override;

    std::optional<InventoryNS::Inventory> die() override;

    int getReloadTime() const;

    void setReloadTime(int reloadTime);

    int getMaxWeight() const;

    void setMaxWeight(int maxWeight);

    int getAccuracy() const;

    void setAccuracy(int accuracy);

//    const InventoryNS::Inventory &getInvetnory() const;

    void setInvetnory(const InventoryNS::Inventory &invetnory);

    [[nodiscard]] const std::optional<WeaponNS::Weapon> &getActiveWeapon() const;

    void setActiveWeapon(const std::optional<WeaponNS::Weapon> &activeWeapon);


private:

    int ReloadTime_;
    int maxWeight_;
    int Accuracy_;
    InventoryNS::Inventory Inventory_;
    std::optional<WeaponNS::Weapon> ActiveWeapon_;
};
}

#endif //LAB3_OPERATIVE_H
