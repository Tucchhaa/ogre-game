#pragma once

#include "network_layer.hpp"

namespace core {

/**
 * Physics simulation and fixed updates are called from the Server.
 * Synchronizes game states between all the clients.
 */
class Server : public NetworkLayer {
protected:
    void tick(float dt) override;
};

};
