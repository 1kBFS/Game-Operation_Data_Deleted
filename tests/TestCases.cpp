//
// Created by Pavel on 06.11.2023.
//
#define CATCH_CONFIG_MAIN
#include "../RoundContainer.h"
#include "../FirstAidKit.h"
#include "../Weapon.h"
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