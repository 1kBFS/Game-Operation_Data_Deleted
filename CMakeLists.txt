cmake_minimum_required(VERSION 3.18)
project(Lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab3 main.cpp Item.cpp Item.h Weapon.cpp Weapon.h RoundContainer.cpp RoundContainer.h FirstAidKit.cpp FirstAidKit.h Inventory.cpp Inventory.h Entity.cpp Entity.h Matrix.cpp Matrix.h Level.cpp Level.h Team.cpp Team.h Cell.cpp Cell.h Operative.cpp Operative.h Wild_Creature.cpp Wild_Creature.h Intelligent_Creature.cpp Intelligent_Creature.h Forager.cpp Forager.h Game.cpp Game.h)
