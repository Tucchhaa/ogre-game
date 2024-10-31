#include "server.hpp"

#include <iostream>

#include "../game.hpp"
#include "../game_event_listener.hpp"
#include "../objects/base_movable_object.hpp"
#include "../physics_world.hpp"
#include "../utils.hpp"

using namespace std;

namespace core {

Server::Server(): NetworkLayer(HostType::Server) {
    m_state = ServerState::STARTING;
}

void Server::init() {
    NetworkLayer::init();
    m_state = ServerState::WAIT_CLIENTS;
    m_LANListener = make_shared<LANListener>(m_host->address.port);
}

void Server::tick(float dt) {
    if(m_state == ServerState::WAIT_CLIENTS) {
        m_LANListener->listen();
    }
    else if(m_state == ServerState::RUNNING) {
        tickGame(dt);
    }
}

void Server::onConnected() {
    cout << "Peer connected" << endl;
    // Note: starts game when one client connected.
    // TODO: start when the user clicks to start
    m_state = ServerState::RUNNING;

    // delete LAN listener
    m_LANListener.reset();
}

void Server::onDisconnected() {
    cout << "Peer disconnected" << endl;
}

void Server::tickGame(float dt) const {
    Game::physics()->stepSimulationFixed(dt);
    GameEventListener::callFixedUpdate(dt);

    ostringstream stream(std::ios::binary);
    int statesCount = 0;

    // preserve space for stateCount
    STREAM_WRITE(stream, statesCount);

    for(auto [ID, object] : BaseMovableObject::instances()) {
        if(object->state() == nullptr)
            continue;

        statesCount++;

        STREAM_WRITE(stream, object->ID);
        object->state()->serialize(stream);
    }

    // move stream point to the beginning
    stream.seekp(0);
    STREAM_WRITE(stream, statesCount);

    // send packet over unreliable channel, because packets will be sent very often
    broadcast(stream, UNRELIABLE_CHANNEL_ID);
}

void Server::broadcast(const ostringstream& stream, enet_uint8 channel_id) const {
    auto* packet = createPacket(stream, channel_id);

    enet_host_broadcast(m_host, channel_id, packet);
    enet_host_flush(m_host);
}

void Server::send(ENetPeer* peer, const ostringstream &stream, enet_uint8 channel_id) const {
    auto* packet = createPacket(stream, channel_id);

    enet_peer_send(peer, RELIABLE_CHANNEL_ID, packet);
    enet_host_flush(m_host);
}

} // end namespace core
