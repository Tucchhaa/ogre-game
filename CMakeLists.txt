cmake_minimum_required(VERSION 3.28)
project(ogre_game)

include(sourceFiles.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
find_package(Bullet CONFIG REQUIRED)
find_package(SDL2 REQUIRED)

get_core_source_files()

find_package(unofficial-enet CONFIG REQUIRED)
link_libraries(unofficial::enet::enet)

add_executable(ogre_game
    src/main.cpp
    ${CORE_SOURCE_FILES}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_include_directories(ogre_game PRIVATE ./vcpkg/installed/arm64-osx/include)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_include_directories(ogre_game PRIVATE ./vcpkg/installed/x64-linux/include)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_include_directories(ogre_game PRIVATE ./vcpkg/installed/x64-windows/include)
endif()

target_link_libraries(ogre_game
    OgreBites
    ${BULLET_LIBRARIES}
    ${SDL2_LIBRARIES}
)
