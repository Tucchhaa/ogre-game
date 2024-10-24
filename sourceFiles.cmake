function(get_core_source_files)
    set(CORE_SOURCE_FILES
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
        PARENT_SCOPE
    )

    return()
endfunction(get_core_source_files)
