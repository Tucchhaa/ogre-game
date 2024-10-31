#include "lan_listener.hpp"

#include <sstream>
#include <string>

#include "../utils.hpp"
#include "const.hpp"

using namespace std;

namespace core {

LANListener::LANListener(unsigned int port) {
    m_port = port;
    m_listener = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
    m_discoveredMessage = createDiscoveredMessage(m_messageBuffer);
    m_listenAddress.host = ENET_HOST_ANY;
    m_listenAddress.port = LAN_LISTEN_PORT;

    // Allow the port to be reused by other applications - this means we can run several servers at once
    enet_socket_set_option(m_listener, ENET_SOCKOPT_REUSEADDR, 1);
    enet_socket_bind(m_listener, &m_listenAddress);
}

LANListener::~LANListener() {
    delete m_messageBuffer;
    enet_socket_shutdown(m_listener, ENET_SOCKET_SHUTDOWN_READ_WRITE);
    enet_socket_destroy(m_listener);
}

void LANListener::listen() const {
    ENetSocketSet set;
    ENET_SOCKETSET_EMPTY(set);
    ENET_SOCKETSET_ADD(set, m_listener);

    // check if any data arrived
    if (enet_socketset_select(m_listener, &set, nullptr, 0) <= 0) return;

    ENetAddress peerAddress;

    // read buffer
    const string message = receiveData(&peerAddress);
    // check if packet is from ogre LANScanner
    if(message != LAN_DISCOVER_MESSAGE) {
        return;
    }

    // send port
    enet_socket_send(m_listener, &peerAddress, &m_discoveredMessage, 1);
}

string LANListener::receiveData(ENetAddress* peerAddress) const {
    char buffer[LAN_DISCOVER_MESSAGE_LEN];
    ENetBuffer payload;
    payload.data = &buffer;
    payload.dataLength = LAN_DISCOVER_MESSAGE_LEN;

    if (enet_socket_receive(m_listener, peerAddress, &payload, 1) <= 0) {
        return "";
    }

    string message(buffer, LAN_DISCOVER_MESSAGE_LEN);
    return message;
}

ENetBuffer LANListener::createDiscoveredMessage(char* buffer) const {
    int bufferLength = (int)LAN_DISCOVERED_MESSAGE_LEN + sizeof(int);
    buffer = new char[bufferLength];

    memcpy(buffer, LAN_DISCOVERED_MESSAGE, LAN_DISCOVERED_MESSAGE_LEN);
    memcpy(buffer + LAN_DISCOVERED_MESSAGE_LEN, &m_port, sizeof(m_port));

    ENetBuffer payload;
    payload.data = buffer;
    payload.dataLength = bufferLength;

    return payload;
}

}