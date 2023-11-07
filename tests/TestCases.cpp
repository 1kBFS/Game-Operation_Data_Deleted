//
// Created by Pavel on 06.11.2023.
//
#define CATCH_CONFIG_MAIN
#include "../Items/RoundContainer.h"
#include "../Items/FirstAidKit.h"
#include "../Items/Weapon.h"
#include "../Items/Inventory.h"
#include "catch.hpp"

TEST_CASE("RoundContainer"){
    RoundNS::RoundContainer container("AK-47 bullets", 0);
    REQUIRE(container.GetTitle() == "AK-47 bullets");
    REQUIRE(container.GetType() == ItemNS::ItemType::CONTAINER);
    REQUIRE(container.extract(5) == 5);
    REQUIRE(container.getSize() == 5);
    REQUIRE(container.extract(7) == 5);
    REQUIRE(container.getSize() == 0);
    REQUIRE_THROWS(container.extract(-1));
}

TEST_CASE("FirstAidKit") {
    FirstAidKitNS::FirstAidKit aid("Йод", 1, 2, 25);
    REQUIRE(aid.GetType() == ItemNS::ItemType::AID_KIT);
    REQUIRE(aid.GetTitle() == "Йод");
    REQUIRE(aid.getHeatPointBoost() == 25);
}

TEST_CASE("Weapon") {
    WeaponNS::Weapon weapon("AK-47", 5);
    REQUIRE(weapon.GetTitle() == "AK-47");
    REQUIRE(weapon.GetType() == ItemNS::ItemType::WEAPON);
    RoundNS::RoundContainer container_good("AK-47 bullets", 5, 20);
    RoundNS::RoundContainer container_low("AK-47 bullets", 5, 0);
    RoundNS::RoundContainer container_bad("M4A4 bullets", 0, 20);

    REQUIRE(weapon.getMagazineSize() == 0);

    REQUIRE_THROWS(weapon.reload(container_bad));
    REQUIRE_THROWS(weapon.reload(container_low));
    REQUIRE(weapon.getMagazineSize() == 0);

    weapon.reload(container_good);
    REQUIRE(weapon.getMagazineSize() == 10);
    REQUIRE(container_good.getSize() == 10);

    REQUIRE(weapon.shot() == 3);
    REQUIRE(weapon.getMagazineSize() == 9);

    weapon.reload(container_good);
    REQUIRE(weapon.getMagazineSize() == 10);
    REQUIRE(container_good.getSize() == 9);

    REQUIRE_THROWS(weapon.reload(container_good));
}

TEST_CASE("Inventory"){
    InventoryNS::Inventory inventory1;
    inventory1.push_back(std::make_unique<RoundNS::RoundContainer>("AK-47 bullets", 1));
    REQUIRE(inventory1.getCurWeight() == 5);
    REQUIRE(inventory1.getSize() == 1);
    // Shows that compiles correct
    for (auto &el : inventory1){
        auto local_container_name = el->GetTitle();
        if (el->GetType() == ItemNS::ItemType::CONTAINER) {
            auto local_container = dynamic_cast<RoundNS::RoundContainer *>(el.get());
            auto local_container_type = local_container->getRoundType();
            local_container->setRoundType(100);
        }
    }
    auto it = inventory1.find("AK-47 bullets");
    REQUIRE(it != inventory1.end());
    REQUIRE((*it)->GetTitle() == "AK-47 bullets");
    auto this_container = dynamic_cast<RoundNS::RoundContainer *>((*it).get());
    REQUIRE(this_container->getRoundType() == 100);

    inventory1.erase(it);
    REQUIRE(inventory1.getSize() == 0);
    REQUIRE(inventory1.getCurWeight() == 0);

    inventory1.push_back(std::make_unique<RoundNS::RoundContainer>("AK-47 bullets #2", 1));
    inventory1.push_back(std::make_unique<WeaponNS::Weapon>("AK-47", 1, 10));
    inventory1.push_back(std::make_unique<FirstAidKitNS::FirstAidKit>("AID"));

    REQUIRE(inventory1.getSize() == 3);
    REQUIRE(inventory1.getCurWeight() == (5+10+1));

    // Move ctor
    InventoryNS::Inventory inventory2 = std::move(inventory1);
    REQUIRE(inventory1.getSize() == 0);
    REQUIRE(inventory1.getCurWeight() == 0);
    REQUIRE(inventory1.begin() == inventory1.end());

    REQUIRE(inventory2.getSize() == 3);
    REQUIRE(inventory2.getCurWeight() == 16);

    // Move assigment operator
    InventoryNS::Inventory inventory3;
    inventory3.push_back(std::make_unique<RoundNS::RoundContainer>("M4A4 bullets #3", 1));
    inventory3 = std::move(inventory2);
    REQUIRE(inventory2.getSize() == 0);
    REQUIRE(inventory2.getCurWeight() == 0);
    REQUIRE(inventory3.getSize() == 3);
    REQUIRE(inventory3.getCurWeight() == 16);

    InventoryNS::Inventory inventory4;
    inventory4.push_back(std::make_unique<RoundNS::RoundContainer>("MP7 bullets #5", 1));
    inventory4.put_all(inventory3);
    REQUIRE(inventory3.getSize() == 0);
    REQUIRE(inventory3.getCurWeight() == 0);
    REQUIRE(inventory4.getSize() == 4);
    REQUIRE(inventory4.getCurWeight() == 21);

    // Throw item
    auto ptr = inventory4.throw_item(inventory4.begin());
    REQUIRE(ptr->GetTitle() == "MP7 bullets #5");
    REQUIRE(inventory4.getSize() == 3);
    REQUIRE(inventory4.getCurWeight() == 16);
}