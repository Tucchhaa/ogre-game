#pragma once

#include "network_layer.hpp"

namespace core {

class Client : public NetworkLayer {
protected:
    void tick(float dt) override;
};

} // end namespace core
