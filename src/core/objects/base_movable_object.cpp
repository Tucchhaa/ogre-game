#include "base_movable_object.hpp"

#include "../game.hpp"
#include "../network_layer/network_layer_manager.hpp"
#include "../network_layer/server.hpp"

namespace core {

void BaseMovableObject::init() {
    setListener(new Listener(this));
    Game::root()->addFrameListener(new FrameListener(this));

    getUserObjectBindings().setUserAny(this);
}

void BaseMovableObject::objectAttached() {
    auto callback = [this](float dt) {
        this->fixedUpdate(dt);
        return this;
    };

    m_fixedUpdateCallbackId = Game::networkLayerManager()->server()->tickEvent.subscribe(callback);
}

void BaseMovableObject::objectDetached() {
    Game::networkLayerManager()->server()->tickEvent.unsubscribe(m_fixedUpdateCallbackId);

    m_fixedUpdateCallbackId = -1;
}

} // end namespace core