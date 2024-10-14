#include "server.hpp"

#include "../game.hpp"
#include "../game_event_listener.hpp"
#include "../objects/base_movable_object.hpp"
#include "../physics_world.hpp"

namespace core {

void Server::tick(float dt) {
    Game::physics()->stepSimulationFixed(dt);
    GameEventListener::callFixedUpdate(dt);

    for(auto [ID, object] : BaseMovableObject::instances()) {
        if(object->state() != nullptr) {
            object->state()->popChanges(); // TODO: collect all changes and send them to the clients
        }
    }
}

} // end namespace core
