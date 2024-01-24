cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "/home/pavel/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
include(FetchContent)
project(Lab3)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        )
FetchContent_MakeAvailable(json)
add_executable(Lab3 main.cpp src/Items/Item.h src/Items/Item.cpp src/Items/RoundContainer.cpp src/Items/RoundContainer.h src/Items/FirstAidKit.h src/Items/FirstAidKit.cpp src/Items/Weapon.cpp src/Items/Weapon.h
        src/Items/Inventory.h src/Items/Inventory.cpp src/Entities/Entity.h src/Entities/Entity.cpp src/Entities/Operative.h src/Entities/Operative.cpp src/Entities/Wild_Creature.h src/Entities/Wild_Creature.cpp src/Entities/Intelligent_Creature.cpp src/Entities/Intelligent_Creature.h src/Entities/Forager.h src/Entities/Forager.cpp
        src/Level/Team.h src/Level/Team.cpp src/Level/Cell.h src/Level/Cell.cpp src/Level/Level.h src/Level/Level.cpp src/Game/Game.h src/Game/Game.cpp src/UI/Game_Controller.cpp src/UI/Game_Controller.h src/UI/Tile_Map.cpp src/UI/Tile_Map.h src/Game/GameConfig.cpp src/Game/GameConfig.h)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI 1 REQUIRED)
target_link_libraries(Lab3 sfml-graphics sfml-audio TGUI::TGUI nlohmann_json::nlohmann_json)
