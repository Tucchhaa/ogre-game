#pragma once

#include "network_base.hpp"
#include "server_info.hpp"

namespace core {

class Client : public NetworkBase {
public:
    Client(): NetworkBase(HostType::Client) {}

    void connect(ServerInfo server);

protected:
    void onConnected() override;

    void onDisconnected() override;

    void onMessage(std::istream& stream) override;

private:
    ENetPeer* m_peer = nullptr;
};

} // end namespace core
