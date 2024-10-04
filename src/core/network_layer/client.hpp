#pragma once

#include "network_layer.hpp"

namespace core {

class Client : public INetworkLayer {
protected:
    void tick(float dt) override;
};

} // end namespace core
