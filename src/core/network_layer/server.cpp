#include "server.hpp"

#include <functional>

#include "../game.hpp"
#include "../objects/base_movable_object.hpp"
#include "../physics_world.hpp"

namespace core {

void TickEvent::fire(const function<void(callback_type)>& emitter) {
    lock_guard _(m_callbacks_mutex);

    for(const auto& [id, callback]: m_callbacks)
        emitter(callback);
}

void Server::tick(float dt) {
    simulatePhysics(dt);
    callFixedUpdate(dt);
}

void Server::simulatePhysics(float dt) {
    Game::physics()->stepSimulationFixed(dt);
}

void Server::callFixedUpdate(float dt) {
    tickEvent.fire([&dt](const function<BaseMovableObject*(float)>& callback) {
        const auto object = callback(dt);

        if(object->state() != nullptr) {
            object->state()->popChanges();
        }
    });
}

} // end namespace core
