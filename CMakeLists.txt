cmake_minimum_required(VERSION 3.18)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

#add_executable(Lab3 main.cpp Item.cpp Item.h Weapon.cpp Weapon.h RoundContainer.cpp RoundContainer.h FirstAidKit.cpp FirstAidKit.h Inventory.cpp Inventory.h Entity.cpp Entity.h Matrix.cpp Matrix.h Level.cpp Level.h Team.cpp Team.h Cell.cpp Cell.h Operative.cpp Operative.h Wild_Creature.cpp Wild_Creature.h Intelligent_Creature.cpp Intelligent_Creature.h Forager.cpp Forager.h Game.cpp Game.h tests/TestCases.cpp tests/catch.hpp)
add_executable(Lab3 tests/TestCases.cpp Items/Item.h Items/Item.cpp tests/catch.hpp Items/RoundContainer.cpp Items/RoundContainer.h Items/FirstAidKit.h Items/FirstAidKit.cpp Items/Weapon.cpp Items/Weapon.h
        Items/Inventory.h Items/Inventory.cpp Entities/Entity.h Entities/Entity.cpp Entities/Operative.h Entities/Operative.cpp Entities/Wild_Creature.h Entities/Wild_Creature.cpp Entities/Intelligent_Creature.cpp Entities/Intelligent_Creature.h Entities/Forager.h Entities/Forager.cpp
        Level/Team.h Level/Team.cpp Level/Cell.h Level/Cell.cpp Level/Level.h Level/Level.cpp Game/Game.h Game/Game.cpp)
