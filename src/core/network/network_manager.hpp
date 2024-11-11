#pragma once

#include <vector>
#include <memory>

#include "server_info.hpp"

namespace core {

class Server;
class Client;
class NetworkBase;
class LANScanner;

class NetworkManager {
    enum class NetworkType {
        /** Used as initial value */
        None,
        /** Use to host a LAN game */
        LANHost,
        /** Use to connect to LAN game */
        LANPeer,
    };

public:
    NetworkManager();
    ~NetworkManager();

    /**
     * Scans LAN to discover servers
     */
    void searchLANServers();

    void initClient();
    void initServer();

    void start() const;

    /**
     * Need to call it after a peer was initialised.
     */
    void stop();

    const std::shared_ptr<NetworkBase>& peer() const { return m_peer; }
    std::shared_ptr<Server> server() const;
    std::shared_ptr<Client> client() const;

    const std::vector<ServerInfo>& getLANServers() const { return m_LANServers; }
    const ServerInfo& getLANServerAt(int index) const { return m_LANServers[index]; }

private:
    NetworkType m_networkType = NetworkType::None;
    std::shared_ptr<NetworkBase> m_peer;
    std::shared_ptr<LANScanner> m_LANScanner;
    std::vector<ServerInfo> m_LANServers;

    std::shared_ptr<NetworkBase> createPeer(NetworkType networkType);
};

} // end namespace core
