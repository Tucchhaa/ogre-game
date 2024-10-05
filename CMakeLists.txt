cmake_minimum_required(VERSION 3.28)
project(ogre_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(./vcpkg/installed/arm64-osx/include)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
link_libraries(OgreBites)

find_package(Bullet CONFIG REQUIRED)
link_libraries(${BULLET_LIBRARIES})

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
        src/core/objects/collider.cpp
        src/core/objects/collider.hpp

        src/core/physics_world.cpp
        src/core/physics_world.hpp
        src/core/collider_drawer.cpp
        src/core/collider_drawer.hpp

        src/core/objects/state.cpp
        src/core/objects/state.hpp

        src/core/network_layer/network_layer_manager.cpp
        src/core/network_layer/network_layer_manager.hpp
        src/core/network_layer/network_layer.cpp
        src/core/network_layer/network_layer.hpp
        src/core/network_layer/server.cpp
        src/core/network_layer/server.hpp
        src/core/network_layer/client.cpp
        src/core/network_layer/client.hpp
)

