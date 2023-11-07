//
// Created by Pavel on 06.11.2023.
//
#define CATCH_CONFIG_MAIN
#include "../RoundContainer.h"
#include "../FirstAidKit.h"
#include "catch.hpp"

TEST_CASE("RoundContainer methods"){
    RoundNS::RoundContainer container("AK-47 bullets", 5);
    REQUIRE(container.GetTitle() == "AK-47 bullets");
    REQUIRE(container.GetType() == ItemNS::ItemType::CONTAINER);
    REQUIRE(container.extract(5) == 5);
    REQUIRE(container.getSize() == 5);
    REQUIRE(container.extract(7) == 5);
    REQUIRE(container.getSize() == 0);
    REQUIRE_THROWS(container.extract(-1));
}

TEST_CASE("FirstAidKit methods") {
    FirstAidKitNS::FirstAidKit aid("Йод", 1, 2, 25);
    REQUIRE(aid.GetType() == ItemNS::ItemType::AID_KIT);
    REQUIRE(aid.GetTitle() == "Йод");
    REQUIRE(aid.getHeatPointBoost() == 25);
}