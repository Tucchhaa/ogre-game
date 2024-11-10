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
    src/core/custom_scene_manager.hpp
    src/core/custom_scene_node.cpp
    src/core/custom_scene_node.hpp
    src/core/ui_manager.cpp
    src/core/ui_manager.hpp

    src/core/objects/base_movable_object.hpp
    src/core/objects/base_movable_object.cpp
    src/core/objects/free_character_controller.cpp
    src/core/objects/free_character_controller.hpp
    src/core/objects/transform.cpp
    src/core/objects/transform.hpp
    src/core/objects/collider.cpp
    src/core/objects/collider.hpp
    src/core/objects/state.hpp
    src/core/objects/state.cpp
    src/core/objects/transform_state.cpp
    src/core/objects/transform_state.hpp

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
    src/core/network_layer/lan_scanner.hpp
    src/core/network_layer/lan_scanner.cpp
    src/core/network_layer/lan_listener.cpp
    src/core/network_layer/lan_listener.hpp
    src/core/network_layer/const.hpp
    src/core/network_layer/server_info.hpp

    src/core/event.hpp
    src/core/utils.hpp
)

set(GAME_SOURCE_FILES
    src/game/galactic_wars_game.cpp
    src/game/galactic_wars_game.hpp

    src/game/ui/main_menu.cpp
    src/game/ui/main_menu.hpp
    src/game/ui/lan_menu.cpp
    src/game/ui/lan_menu.hpp
    src/game/ui/lan_peer_menu.cpp
    src/game/ui/lan_peer_menu.hpp

    src/game/scenes/menu_scene.cpp
    src/game/scenes/menu_scene.hpp
    src/game/scenes/demo_scene.cpp
    src/game/scenes/demo_scene.hpp
)