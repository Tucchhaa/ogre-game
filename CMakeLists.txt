cmake_minimum_required(VERSION 3.28)
project(ogre_game)

include(sourceFiles.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    # use static build on WIN32 so ogre can import Assimp

    include_directories(./vcpkg/installed/x64-windows-static/include)

    set(CMAKE_PREFIX_PATH
        ./vcpkg/installed/x64-windows-static
        ./vcpkg/installed/x64-windows-static/share
    )
    set(VCPKG_TARGET_TRIPLET "x64-windows-static")
    set(VCPKG_CRT_LINKAGE static)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    # without this Ogre can't open the window to prompt render options
#    set(RESOURCE_RC ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/buildtrees/ogre/src/v14.2.2-365de132fa.clean/Components/Bites/misc/OgreWin32Resources.rc)

endif()

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
find_package(Bullet CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(unofficial-enet CONFIG REQUIRED)

add_executable(ogre_game
    src/main.cpp
    ${CORE_SOURCE_FILES}
    ${RESOURCE_RC}
)

target_link_libraries(ogre_game
    OgreBites
    ${BULLET_LIBRARIES}
    ${SDL2_LIBRARIES}
    unofficial::enet::enet
    Ws2_32
)
