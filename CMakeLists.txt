cmake_minimum_required(VERSION 3.28)
project(ogre_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(./vcpkg/installed/arm64-osx/include)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
link_libraries(OgreBites)

add_executable(ogre_game main.cpp)

