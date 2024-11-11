#pragma once

#include <enet/enet.h>

#include "../game_loop_thread.hpp"

namespace core {

enum class HostType {
    Client,
    Server,
};

/*
 * Base class for Client and Server
 */
class NetworkBase : public GameLoopThread {
public:
    explicit NetworkBase(HostType hostType): m_hostType(hostType) {}

    virtual void init();

protected:
    static constexpr enet_uint8 UNRELIABLE_CHANNEL_ID = 0;
    static constexpr enet_uint8 RELIABLE_CHANNEL_ID = 1;

    ENetHost* m_host = nullptr;

    void tick(float dt) override;

    /**
     * If server, then called when a client connects to the server.
     * If client, then called when it connects to a server.
     */
    virtual void onConnected() {}

    /**
     * If server, then called when a client disconnects from the server.
     * If client, then called when the client was disconnected from the server.
     */
    virtual void onDisconnected() {}

    /**
     * If client, then called when a message from the server was received.
     * If server, then called when a message from a client was received.
     */
    virtual void onMessage(std::istream& stream) {}

    static ENetPacket* createPacket(const std::ostringstream &stream, enet_uint8 channel_id);

private:
    HostType m_hostType;

    ENetHost* createHost() const;

    void handleEnetEvent();
};

} // end namespace core
