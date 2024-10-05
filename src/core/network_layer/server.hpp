#pragma once

#include "network_layer.hpp"
#include "../event.hpp"
#include "../objects/base_movable_object.hpp"

namespace core {

class TickEvent : public TemplateEvent<BaseMovableObject*(float)> {
public:
    void fire() override { throw runtime_error("Not implemented"); }
    void fire(const function<void(callback_type)>& emitter);
};

/**
 * Physics simulation and fixed updates are called from the Server.
 * Synchronizes game states between all the clients.
 */
class Server : public INetworkLayer {
public:
    /**
     * For BaseMovableObject::fixedUpdate
     */
    TickEvent tickEvent;

protected:
    void tick(float dt) override;

private:
    void simulatePhysics(float dt);

    void callFixedUpdate(float dt);
};

};
