#include "lan_scanner.hpp"

#include <sstream>

#include "../utils.hpp"
#include "const.hpp"

using namespace std;

namespace core {

LANScanner::LANScanner() {
    m_scanner = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM);
    m_discoverMessage = createDiscoverMessage();

    m_broadcastAddress.host = ENET_HOST_BROADCAST;
    m_broadcastAddress.port = LAN_LISTEN_PORT;

    // set socket option to broadcast
    enet_socket_set_option(m_scanner, ENET_SOCKOPT_BROADCAST, 1);
    enet_socket_set_option(m_scanner, ENET_SOCKOPT_RCVTIMEO, RESPONSE_TIMEOUT);
}

LANScanner::~LANScanner() {
    enet_socket_shutdown(m_scanner, ENET_SOCKET_SHUTDOWN_READ_WRITE);
    enet_socket_destroy(m_scanner);
}

vector<ServerInfo> LANScanner::scan() const {
    enet_socket_send(m_scanner, &m_broadcastAddress, &m_discoverMessage, 1);

    ENetAddress serverAddress;
    unsigned int serverPort;

    vector<ServerInfo> result;

    while(result.size() < MAX_SERVERS) {
        const string message = receiveData(&serverAddress, &serverPort);

        if(message.empty()) {
            break;
        }

        result.push_back({ serverAddress.host, serverPort });
    }

    return result;
}

string LANScanner::receiveData(ENetAddress* serverAddress, unsigned int* serverPort) const {
    const unsigned int bufferLength = LAN_DISCOVERED_MESSAGE_LEN + sizeof(int);
    const std::unique_ptr<char[]> buffer(new char[bufferLength]);

    ENetBuffer payload;
    payload.data = buffer.get();
    payload.dataLength = bufferLength;

    if(enet_socket_receive(m_scanner, serverAddress, &payload, 1) <= 0) {
        return "";
    }

    string message(buffer.get(), LAN_DISCOVERED_MESSAGE_LEN);
    // extract server port
    memcpy(serverPort, buffer.get() + LAN_DISCOVERED_MESSAGE_LEN, sizeof(int));

    return message;
}

ENetBuffer LANScanner::createDiscoverMessage() {
    ENetBuffer buffer;
    buffer.data = (void*)LAN_DISCOVER_MESSAGE;
    buffer.dataLength = LAN_DISCOVER_MESSAGE_LEN;

    return buffer;
}

}
