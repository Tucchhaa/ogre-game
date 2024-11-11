#include "network_base.hpp"

#include <sstream>

#include "../utils.hpp"

using namespace std;

namespace core {

NetworkBase::~NetworkBase() {
    NetworkBase::stop();
}

long long NetworkBase::currentUpdateTimestamp() {
    std::lock_guard _(updateTimestampMutex);
    return m_currentUpdateTimestamp;
}

long long NetworkBase::previousUpdateTimestamp() {
    std::lock_guard _(updateTimestampMutex);
    return m_previousUpdateTimestamp;
}

void NetworkBase::init() {
    m_host = createHost();

    if(m_host == nullptr) {
        throw runtime_error("An error occurred while trying to create an ENet host.");
    }
}

void NetworkBase::start() {
    m_running.store(true);

    m_tickThread = thread([this]() {
        constexpr float dt = MILLISECONDS_BETWEEN_TICKS/1000.;
        constexpr auto interval = chrono::milliseconds(MILLISECONDS_BETWEEN_TICKS);

        auto nextTick = std::chrono::steady_clock::now();

        {
            lock_guard _(updateTimestampMutex);
            m_currentUpdateTimestamp = utils::getTimestamp();
        }

        while(m_running.load()) {
            auto now = std::chrono::steady_clock::now();

            {
                lock_guard _(updateTimestampMutex);
                m_previousUpdateTimestamp = m_currentUpdateTimestamp;
                m_currentUpdateTimestamp = utils::getTimestamp() + MILLISECONDS_BETWEEN_TICKS;
            }

            if(now >= nextTick) {
                handleEnetEvent();
                tick(dt);

                nextTick = now + interval;
            }

            this_thread::sleep_until(nextTick);
        }
    });
}

void NetworkBase::stop() {
    if(m_running.load() == false) {
        return;
    }

    m_running.store(false);

    if (m_tickThread.joinable()) {
        m_tickThread.join();
    }
}

ENetHost* NetworkBase::createHost() const {
    constexpr int CLIENTS_NUMBER = 32;
    constexpr int CHANNELS_NUMBER = 2;
    constexpr int BANDWIDTH_IN = 0;
    constexpr int BANDWIDTH_OUT = 0;

    if(m_hostType == HostType::Server) {
        ENetAddress address;
        address.host = ENET_HOST_ANY;
        address.port = ENET_PORT_ANY;

        return enet_host_create(
            &address,
            CLIENTS_NUMBER, /* allow up to CLIENTS_NUMBER client connections */
            CHANNELS_NUMBER, BANDWIDTH_IN, BANDWIDTH_OUT
        );
    }

    return enet_host_create(
        nullptr /* create a client host */,
        1       /* only allow 1 outgoing connection */,
        CHANNELS_NUMBER, BANDWIDTH_IN, BANDWIDTH_OUT
    );
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

            istringstream stream(data, std::ios::binary);
            onMessage(stream);

            break;
    }
}

} // end namespace core
