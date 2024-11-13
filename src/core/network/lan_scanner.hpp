#pragma once

#include <memory>
#include <vector>
#include <string>

#include <enet/enet.h>

#include "server_info.hpp"

namespace core {

class LANScanner {
public:
    LANScanner();

    ~LANScanner();

    std::vector<ServerInfo> scan() const;

private:
    static constexpr int RESPONSE_TIMEOUT = 250;
    static constexpr int MAX_SERVERS = 5;

    ENetSocket m_scanner;
    ENetAddress m_broadcastAddress{};
    ENetBuffer m_discoverMessage{};

    std::string receiveData(ENetAddress* serverAddress, unsigned int* serverPort) const;

    static ENetBuffer createDiscoverMessage();
};

}
