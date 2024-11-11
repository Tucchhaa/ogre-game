#pragma once

#include <vector>
#include <memory>

#include "server_info.hpp"

namespace core {

class Server;
class Client;
class NetworkBase;
class LANScanner;

enum class PeerType {
    /** Used as initial value */
    None,
    /** Use to host a single player game */
    SinglePlayer,
    /** Use to host a LAN game */
    LANHost,
    /** Use to connect to LAN game */
    LANPeer,
};

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    long long previousUpdateTimestamp() const;

    long long currentUpdateTimestamp() const;

    /**
     * Launches LAN scanner to find if there are some servers
     */
    bool searchLANGames();

    void initClient();
    void initServer();
    void initSinglePlayer();

    void start() const;

    /**
     * Need to call it after a peer was initialised.
     */
    void stop();

    std::shared_ptr<Server> server() const;
    std::shared_ptr<Client> client() const;

private:
    PeerType m_peerType = PeerType::None;
    std::shared_ptr<NetworkBase> m_peer;
    std::shared_ptr<LANScanner> m_LANScanner;
    std::vector<ServerInfo> m_LANServers;

    // std::shared_ptr<NetworkBase> createNetworkPeer(PeerType peerType);
    std::shared_ptr<NetworkBase> createServer() const;
    std::shared_ptr<NetworkBase> createClient();
};

} // end namespace core
