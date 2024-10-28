cmake_minimum_required(VERSION 3.28)
project(ogre_game)

include(sourceFiles.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake)

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

if(WIN32)
    # enable static build
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # enable ogre static import TODO: check if has effect
    set(OGRE_STATIC ON)
endif()

target_link_libraries(ogre_game
    OgreBites
    ${BULLET_LIBRARIES}
    ${SDL2_LIBRARIES}
)
