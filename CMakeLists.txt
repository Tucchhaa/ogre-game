cmake_minimum_required(VERSION 3.28)
project(ogre_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(./vcpkg/installed/arm64-osx/include)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
link_libraries(OgreBites)

add_executable(ogre_game
        src/main.cpp
        src/core/input.cpp
        src/core/input.hpp
        src/core/game.cpp
        src/core/game.hpp
        src/core/scene.cpp
        src/core/scene.hpp
        src/core/objects/base_movable_object.hpp
        src/core/objects/free_character_controller.cpp
        src/core/objects/free_character_controller.hpp
)

