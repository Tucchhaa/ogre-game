#pragma once

#include "lan_listener.hpp"
#include "network_base.hpp"

#include "../event.hpp"

namespace core {

enum class ServerState {
    /**
     * initialization
     */
    STARTING,
    /**
     * clients can connect to server
     */
    WAIT_CLIENTS,
    /**
     * game started, clients can't connect
     */
    RUNNING
};

/**
 * Physics simulation and fixed updates are called from the Server.
 * Synchronizes game states between all the clients.
 */
class Server : public NetworkBase {
public:
    /// An event of clients connecting or disconnecting
    Event<> onClientsChange;

    Server();

    void init() override;


    /// Switches state to running and start the game
    void startGame();

    void stop() override;

    /**
     * Returns the count of connected to the server clients
     */
    unsigned int getClientsCount() const;

protected:
    void tick(float dt) override;

    void onConnected() override;

    void onDisconnected() override;

private:
    std::atomic<ServerState> m_state{};

    std::shared_ptr<LANListener> m_LANListener;

    void tickGame(float dt) const;

    /**
     * Sends data to all connected clients.
     */
    void broadcast(const std::ostringstream& stream, enet_uint8 channel_id) const;

    /**
     * Sends data to a specific client.
     */
    void send(ENetPeer* peer, const std::ostringstream &stream, enet_uint8 channel_id) const;
};

};
