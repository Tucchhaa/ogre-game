#include "client.hpp"

#include <iostream>
#include <sstream>

#include "../utils.hpp"
#include "../objects/base_movable_object.hpp"

core::Client::Client(ServerInfo server): NetworkLayer(HostType::Client),
    m_server(server)
{ }

void core::Client::init() {
    NetworkLayer::init();

    // connect to server
    ENetAddress serverAddress;
    serverAddress.host = m_server.host;
    serverAddress.port = m_server.port;

    ENetPeer* peer = enet_host_connect(m_host, &serverAddress, 2, 0);

    if(peer == nullptr) {
        throw runtime_error("Cannot connect to server");
    }

    // TODO: if connection was not established, then need to reset peer
    // enet_peer_reset(peer)
}

void core::Client::onConnected() {
    cout << "Connected to server at port: " << m_server.port << endl;
}

void core::Client::onMessage(istream& stream) {
    int statesCount;
    STREAM_READ(stream, statesCount);

    for(int i=0; i < statesCount; i++) {
        int objectId;
        STREAM_READ(stream, objectId);

        auto object = BaseMovableObject::getInstance(objectId);
        object->state()->deserialize(stream);
    }
}

void core::Client::tick(float dt) { }
