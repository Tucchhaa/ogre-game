#include "network_base.hpp"

#include <sstream>

using namespace std;

namespace core {

void NetworkBase::init() {
    m_host = createHost();
}

void NetworkBase::stop() {
    GameLoopThread::stop();
    enet_host_destroy(m_host);
}

void NetworkBase::tick(float dt) {
    handleEnetEvent();
}

ENetHost* NetworkBase::createHost() const {
    constexpr int CLIENTS_NUMBER = 32;
    constexpr int CHANNELS_NUMBER = 2;
    constexpr int BANDWIDTH_IN = 0;
    constexpr int BANDWIDTH_OUT = 0;

    ENetHost* host;

    if(m_hostType == HostType::Server) {
        ENetAddress address;
        address.host = ENET_HOST_ANY;
        address.port = ENET_PORT_ANY;

        host = enet_host_create(
            &address,
            CLIENTS_NUMBER, /* allow up to CLIENTS_NUMBER client connections */
            CHANNELS_NUMBER, BANDWIDTH_IN, BANDWIDTH_OUT
        );
    }
    else {
        host = enet_host_create(
            nullptr /* create a client host */,
            1       /* only allow 1 outgoing connection */,
            CHANNELS_NUMBER, BANDWIDTH_IN, BANDWIDTH_OUT
        );
    }

    if(host == nullptr) {
        throw runtime_error("An error occurred while trying to create an ENet host.");
    }

    return host;
}

ENetPacket* NetworkBase::createPacket(const ostringstream &stream, enet_uint8 channel_id) {
    const string data = stream.str();
    const auto packetType =
        channel_id == UNRELIABLE_CHANNEL_ID
            ? ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT
            : ENET_PACKET_FLAG_RELIABLE;

    auto* packet = enet_packet_create(data.c_str(), data.size(), packetType);

    return packet;
}

void NetworkBase::handleEnetEvent() {
    ENetEvent event;
    enet_host_service(m_host, &event, 0);

    switch(event.type) {
        case ENET_EVENT_TYPE_NONE:
            break;

        case ENET_EVENT_TYPE_CONNECT:
            onConnected();
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            onDisconnected();
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            const auto data = string(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
            enet_packet_destroy(event.packet);

            istringstream stream(data, std::ios::binary);
            onMessage(stream);

            break;
    }
}

} // end namespace core
