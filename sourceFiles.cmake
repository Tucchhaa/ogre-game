set(CORE_SOURCE_FILES
    src/core/event.hpp
    src/core/game.cpp
    src/core/game.hpp
    src/core/game_event_listener.hpp
    src/core/game_event_listener.cpp
    src/core/game_loop_thread.cpp
    src/core/game_loop_thread.hpp
    src/core/input.cpp
    src/core/input.hpp
    src/core/ui_manager.cpp
    src/core/ui_manager.hpp
    src/core/utils.hpp
    src/core/window_manager.cpp
    src/core/window_manager.hpp

    src/core/network/client.cpp
    src/core/network/client.hpp
    src/core/network/const.hpp
    src/core/network/lan_listener.cpp
    src/core/network/lan_listener.hpp
    src/core/network/lan_scanner.hpp
    src/core/network/lan_scanner.cpp
    src/core/network/network_base.cpp
    src/core/network/network_base.hpp
    src/core/network/network_manager.cpp
    src/core/network/network_manager.hpp
    src/core/network/server.cpp
    src/core/network/server.hpp
    src/core/network/server_info.hpp

    src/core/objects/base_movable_object.hpp
    src/core/objects/base_movable_object.cpp
    src/core/objects/free_character_controller.cpp
    src/core/objects/free_character_controller.hpp
    src/core/objects/transform.cpp
    src/core/objects/transform.hpp
    src/core/objects/collider.cpp
    src/core/objects/collider.hpp

    src/core/objects/state/state.hpp
    src/core/objects/state/state.cpp
    src/core/objects/state/transform_state.cpp
    src/core/objects/state/transform_state.hpp

    src/core/scene/custom_scene_manager.hpp
    src/core/scene/custom_scene_manager.cpp
    src/core/scene/custom_scene_node.cpp
    src/core/scene/custom_scene_node.hpp
    src/core/scene/scene.cpp
    src/core/scene/scene.hpp

    src/core/physics/collider_drawer.cpp
    src/core/physics/collider_drawer.hpp
    src/core/physics/physics_world.cpp
    src/core/physics/physics_world.hpp
    src/core/physics/tools.cpp
    src/core/physics/tools.hpp
)

set(GAME_SOURCE_FILES
    src/game/galactic_wars_game.cpp
    src/game/galactic_wars_game.hpp

    src/game/ui/fighter_indicators.cpp
    src/game/ui/fighter_indicators.hpp
    src/game/ui/main_menu.cpp
    src/game/ui/main_menu.hpp
    src/game/ui/lan_menu.cpp
    src/game/ui/lan_menu.hpp
    src/game/ui/lan_peer_menu.cpp
    src/game/ui/lan_peer_menu.hpp
    src/game/ui/lan_host_menu.cpp
    src/game/ui/lan_host_menu.hpp

    src/game/scenes/menu_scene.cpp
    src/game/scenes/menu_scene.hpp
    src/game/scenes/demo_scene.cpp
    src/game/scenes/demo_scene.hpp
    src/game/scenes/space_scene.cpp
    src/game/scenes/space_scene.hpp

    src/game/objects/star_fighter_controller.cpp
    src/game/objects/star_fighter_controller.hpp

    src/game/objects/star_fighters/base.cpp
    src/game/objects/star_fighters/base.hpp
    src/game/objects/star_fighters/fighter.cpp
    src/game/objects/star_fighters/fighter.hpp
)