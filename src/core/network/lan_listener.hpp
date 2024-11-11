#pragma once

#include <string>
#include <vector>
#include <memory>
#include <enet/enet.h>

namespace core {

class LANListener {
public:
    explicit LANListener(unsigned int port);

    ~LANListener();

    /**
     * Sends reply to discover messages sent by @LANScanner if any
     */
    void listen() const;

    std::string receiveData(ENetAddress* peerAddress) const;

private:
    unsigned int m_port;
    ENetSocket m_listener;
    ENetAddress m_listenAddress{};

    char* m_messageBuffer = nullptr;
    ENetBuffer m_discoveredMessage{};

    ENetBuffer createDiscoveredMessage();
};

}
