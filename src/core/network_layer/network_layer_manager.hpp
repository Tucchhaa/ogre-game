#pragma once

#include <vector>

#include "server_info.hpp"

using namespace std;

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

    shared_ptr<NetworkLayer> networkLayer() const { return m_networkLayer; }
    shared_ptr<Server> server() const;
    shared_ptr<Client> client() const;

private:
    NetworkType m_networkType = NetworkType::None;
    shared_ptr<NetworkLayer> m_networkLayer;
    shared_ptr<LANScanner> m_LANScanner;
    vector<ServerInfo> m_LANServers;

    shared_ptr<NetworkLayer> createNetworkLayer(NetworkType gameType);
};

} // end namespace core
