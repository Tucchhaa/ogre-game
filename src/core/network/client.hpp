#pragma once

#include "network_base.hpp"
#include "server_info.hpp"

namespace core {

class Client : public NetworkBase {
public:
    explicit Client(ServerInfo server);

    void init() override;

protected:
    void onConnected() override;

    void onMessage(std::istream& stream) override;

    void tick(float dt) override;

private:
    ServerInfo m_server;
};

} // end namespace core
