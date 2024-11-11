#include "client.hpp"

#include <sstream>

#include "../utils.hpp"
#include "../objects/base_movable_object.hpp"

using namespace std;

namespace core {

void Client::connect(const ServerInfo server) {
    ENetAddress serverAddress;
    serverAddress.host = server.host;
    serverAddress.port = server.port;

    m_peer = enet_host_connect(m_host, &serverAddress, 2, 0);

    if(m_peer == nullptr) {
        throw runtime_error("No available peers for initiating an ENet connection.");
    }
}

void Client::onDisconnected() {
    enet_peer_reset(m_peer);
    printf("Disconnected from server");
}

void Client::onConnected() {
    printf("Connected to server");
}

void Client::onMessage(istream& stream) {
    int statesCount;
    STREAM_READ(stream, statesCount);

    for(int i=0; i < statesCount; i++) {
        int objectId;
        STREAM_READ(stream, objectId);

        auto object = BaseMovableObject::getInstance(objectId);
        object->state()->deserialize(stream);
    }
}

} // end namespace core
