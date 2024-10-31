#pragma once

#include "network_layer.hpp"
#include "server_info.hpp"

namespace core {

class Client : public NetworkLayer {
public:
    explicit Client(ServerInfo server);

protected:
    void init() override;

    void onConnected() override;

    void onMessage(istream& stream) override;

    void tick(float dt) override;

private:
    ServerInfo m_server;
};

} // end namespace core
