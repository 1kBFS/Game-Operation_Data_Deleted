//
// Created by Pavel on 06.11.2023.
//
#define CATCH_CONFIG_MAIN
#include "../Items/RoundContainer.h"
#include "../Items/FirstAidKit.h"
#include "../Items/Weapon.h"
#include "../Items/Inventory.h"

#include "../Entities/Operative.h"
#include "../Entities/Wild_Creature.h"
#include "../Entities/Intelligent_Creature.h"

#include "../Level/Level.h"
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

TEST_CASE("OPERATIVE") {
    // init operative with one weapon in hand and one in inventory
    EntityNS::Operative operative_1("Storm Trooper"), operative_to_kill("Enemy", 100, 100, 6, 6, 1, 1, 2, 15, 0);
    REQUIRE(operative_1.getType() == EntityNS::EntityType::OPERATIVE);
    WeaponNS::Weapon first_active_weapon("AK-47", 1, 5);
    operative_1.setActiveWeapon(first_active_weapon);
    InventoryNS::Inventory init_inventory, nonPlayerInventory;
    init_inventory.push_back(std::make_unique<WeaponNS::Weapon>("M4A4-1", 1, 4));
    operative_1.setInvetnory(std::move(init_inventory));

    // changing weapon
    operative_1.change_weapon(0);
    REQUIRE(operative_1.getActiveWeaponTitle() == "M4A4-1");
    REQUIRE(operative_1.getCurrentWeight() == 9);

    // take new_item
    nonPlayerInventory.push_back(std::make_unique<RoundNS::RoundContainer>("MP7 bullets #5", 1, 10, 10)); // too large
    nonPlayerInventory.push_back(std::make_unique<FirstAidKitNS::FirstAidKit>("Йод", 1, 2, 25));

    REQUIRE_THROWS(operative_1.take_item(nonPlayerInventory, 2)); // incorrect index
    REQUIRE_THROWS(operative_1.take_item(nonPlayerInventory, 0)); // two large item

    operative_1.take_item(nonPlayerInventory, 1);
    REQUIRE(operative_1.getCurrentWeight() == 10);
    REQUIRE(nonPlayerInventory.getSize() == 1);

    // throw item
    auto discarded_item = operative_1.throw_item(1);
    REQUIRE(discarded_item->GetTitle() == "Йод");
    REQUIRE(operative_1.getCurrentWeight() == 9);
    REQUIRE_THROWS(operative_1.throw_item(1));

    // make shot
    REQUIRE_THROWS(operative_1.shot(operative_to_kill)); // magazine is empty by default
    RoundNS::RoundContainer container("Assault bullets", 1, 1);
    operative_1.reload(container); // reload weapon, now there are 1 bullet in weapon
    REQUIRE(operative_1.shot(operative_to_kill) == true);
    REQUIRE(operative_to_kill.getCurHeatPoint() == 97); // 3 damage hp, 100% accuracy now for test
    REQUIRE(operative_1.getCurTime() == 94); // 1 time unit to shot

    REQUIRE_THROWS(operative_to_kill.shot(operative_1)); // no weapon is provided
    operative_to_kill.setActiveWeapon(first_active_weapon);
    container.setSize(1);
    operative_to_kill.reload(container);
    REQUIRE(operative_to_kill.shot(operative_1) == false); // 0% accuracy

    // die
    auto special_item_ptr = std::make_unique<FirstAidKitNS::FirstAidKit>("TEST MEDICINE", 1, 2, 25);
    auto address = &(*special_item_ptr);
    operative_to_kill.put_item(std::move(special_item_ptr));

    operative_to_kill.setCurHeatPoint(0);
    auto opt_inventory = operative_to_kill.die();
    REQUIRE(opt_inventory.has_value() == true);
    REQUIRE(opt_inventory->getSize() == 2);
    auto& ptr = *(opt_inventory->begin());
    REQUIRE(ptr->GetTitle() == "TEST MEDICINE");
    REQUIRE(&(*ptr) == address);

}

TEST_CASE("WILD CREATURE") {
    // move
    EntityNS::WildCreature wild("wild", 1, 100);
    wild.setCurTime(1);
    REQUIRE_THROWS(wild.move(1, 1));
    wild.move(1, 0);
    REQUIRE(wild.getPos() == std::make_pair(1, 0));
    REQUIRE_THROWS(wild.move(-1, -1));
    REQUIRE_THROWS(wild.move(1, 1)); // no time
    // attack
    EntityNS::Operative operative_1("Storm Trooper");
    wild.setCurTime(1);
    operative_1.setCurTime(1);
    REQUIRE_THROWS(wild.shot(operative_1) == false); // not in the same cell
    operative_1.move(1, 0);
    REQUIRE(wild.shot(operative_1) == true);
    REQUIRE(operative_1.getCurHeatPoint() == 99);
    REQUIRE(wild.getCurTime() == 0);
    REQUIRE_THROWS(wild.shot(operative_1)); // not enough time

}

TEST_CASE("INTELLIGENT_CREATURE") {
    EntityNS::IntelligentCreature intelligentCreature("intelligent", 100);
    intelligentCreature.setCurTime(10);
    EntityNS::WildCreature enemy("wild", 1, 1);

    // shot
    REQUIRE_THROWS(intelligentCreature.shot(enemy)); // no weapon is provided
    auto weapon_to_take = std::make_unique<WeaponNS::Weapon>("Ak-47", 1, 1, 1); // weapon with 1 bullet, 3 damage
    auto weapon_to_takeAddr =&(*weapon_to_take);
    intelligentCreature.put_weapon(std::move(weapon_to_take));
    REQUIRE(intelligentCreature.shot(enemy) == true);
    REQUIRE(enemy.getCurHeatPoint() == 97);
    REQUIRE_THROWS(intelligentCreature.shot(enemy)); // no bullets

    // try to take another weapon
    auto another_weapon = std::make_unique<WeaponNS::Weapon>("M4A1", 1, 1, 1); // weapon with 1 bullet, 3 damage
    REQUIRE_THROWS(intelligentCreature.put_weapon(std::move(another_weapon))); // weapon already exists
    // throw weapon
    auto weapon_from_hand = intelligentCreature.throw_weapon();
    REQUIRE(weapon_to_takeAddr == &(*weapon_from_hand));
    REQUIRE(weapon_from_hand->GetTitle() == weapon_to_takeAddr->GetTitle());

    // put weapon
    intelligentCreature.put_weapon(std::move(another_weapon));
    REQUIRE(intelligentCreature.shot(enemy) == true);
    REQUIRE(enemy.getCurHeatPoint() == 94);

    InventoryNS::Inventory inventory;
    inventory.push_back(std::make_unique<FirstAidKitNS::FirstAidKit>("Medicine"));
    inventory.push_back(std::move(weapon_from_hand));

    // take weapon from inventory
    REQUIRE_THROWS(intelligentCreature.take_item(inventory, 1)); // weapon already exists
    auto temp_weapon = intelligentCreature.throw_weapon();
    REQUIRE_THROWS(intelligentCreature.take_item(inventory, 0)); // bad item is provided(aid, not weapon)
    intelligentCreature.take_item(inventory, 1); // take AK-47
    REQUIRE(inventory.getSize() == 1);
    auto temp_smrtPtr = intelligentCreature.throw_weapon();
    REQUIRE(weapon_to_takeAddr == &(*temp_smrtPtr));
    REQUIRE(weapon_to_takeAddr->GetTitle() == temp_smrtPtr->GetTitle());
    // die
    auto ptr = std::make_unique<WeaponNS::Weapon>("MP-7", 1);
    auto ptr_addr = &(*ptr);
    intelligentCreature.put_weapon(std::move(ptr));
    intelligentCreature.setCurHeatPoint(0);
    auto items = intelligentCreature.die().value();
    REQUIRE(items.getSize() == 1);
    auto &smrt_ptr = *items.begin();
    REQUIRE(&(*smrt_ptr) == ptr_addr);

}

TEST_CASE("LEVEL") {
    LevelNS::Level level(3);

}