#pragma once

#include <vector>
#include <memory>

#include "server_info.hpp"

namespace core {

class Server;
class Client;
class NetworkLayer;
class LANScanner;

enum class NetworkType {
    /** Used as initial value */
    None,
    /** Use to host a single player game */
    SinglePlayer,
    /** Use to host a LAN game */
    LANHost,
    /** Use to connect to LAN game */
    LANPeer,
};

class NetworkLayerManager {
public:
    NetworkLayerManager();
    ~NetworkLayerManager();

    /**
     * Launches LAN scanner to find if there are some servers
     */
    bool searchLANGames();

    /**
     * Called before starting game. Initializes client or server depending on the gameType
     */
    void initNetworkLayer(NetworkType gameType);

    void start() const;
    void stop();

    std::shared_ptr<NetworkLayer> networkLayer() const { return m_networkLayer; }
    std::shared_ptr<Server> server() const;
    std::shared_ptr<Client> client() const;

private:
    NetworkType m_networkType = NetworkType::None;
    std::shared_ptr<NetworkLayer> m_networkLayer;
    std::shared_ptr<LANScanner> m_LANScanner;
    std::vector<ServerInfo> m_LANServers;

    std::shared_ptr<NetworkLayer> createNetworkLayer(NetworkType gameType);
};

} // end namespace core
