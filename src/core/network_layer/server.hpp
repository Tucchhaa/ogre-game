#pragma once

#include "network_layer.hpp"

namespace core {

class Server : public INetworkLayer {
protected:
    void tick(float dt) override;

private:
    void simulatePhysics(float dt);

    void callFixedUpdate(float dt);
};

};
