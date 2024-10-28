cmake_minimum_required(VERSION 3.28)
project(ogre_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include_directories(./vcpkg/installed/arm64-osx/include)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(./vcpkg/installed/x64-linux/include)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include_directories(./vcpkg/installed/x64-windows-static/include)

    set(CMAKE_PREFIX_PATH
        ./vcpkg/installed/x64-windows-static
        ./vcpkg/installed/x64-windows-static/share
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/share/stb)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows-static/share/jxr)
    set(RESOURCE_RC ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/buildtrees/ogre/src/v14.2.2-365de132fa.clean/Components/Bites/misc/OgreWin32Resources.rc)
endif()

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
link_libraries(OgreBites)

find_package(Bullet CONFIG REQUIRED)
link_libraries(${BULLET_LIBRARIES})

find_package(SDL2 REQUIRED)
link_libraries(${SDL2_LIBRARIES})

add_executable(ogre_game
        src/main.cpp
        ${RESOURCE_RC}
        src/core/input.cpp
        src/core/input.hpp
        src/core/game.cpp
        src/core/game.hpp
        src/core/scene.cpp
        src/core/scene.hpp
        src/core/window_manager.cpp
        src/core/window_manager.hpp
        src/core/game_event_listener.hpp
        src/core/game_event_listener.cpp

        src/core/objects/base_movable_object.hpp
        src/core/objects/base_movable_object.cpp
        src/core/objects/free_character_controller.cpp
        src/core/objects/free_character_controller.hpp
        src/core/objects/collider.cpp
        src/core/objects/collider.hpp
        src/core/objects/state.hpp
        src/core/objects/state.cpp

        src/core/physics_world.cpp
        src/core/physics_world.hpp
        src/core/collider_drawer.cpp
        src/core/collider_drawer.hpp

        src/core/network_layer/network_layer_manager.cpp
        src/core/network_layer/network_layer_manager.hpp
        src/core/network_layer/network_layer.cpp
        src/core/network_layer/network_layer.hpp
        src/core/network_layer/server.cpp
        src/core/network_layer/server.hpp
        src/core/network_layer/client.cpp
        src/core/network_layer/client.hpp

        src/core/event.hpp
        src/core/utils.hpp
)

